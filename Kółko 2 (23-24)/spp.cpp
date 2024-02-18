#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct Przedzial {
	int pocz, kon, warstwy, ilosc;
};
struct Punkt {
	ll x, y, z;
};
struct Klocek {
	Punkt a, b;
};
struct Brzeg {
	ll x1, x2, y;
	bool czy_pocz;
};

const int MAX_Z = 10;
const int MAX = 3 * 100 * 1000;
const int R = (1 << 20);
Przedzial tree[2 * R];
Klocek wej[MAX + 1];
Brzeg brzegi[2 * MAX + 1];

bool na_poziomie(Klocek& klocek, int z) {
	return klocek.a.z <= z && z <= klocek.b.z;
}

void dodaj(ll a, ll b, int v, int x) {
	if (tree[v].kon < a || b < tree[v].pocz) return;
	if (a <= tree[v].pocz && tree[v].kon <= b) {
		tree[v].warstwy += x;
	} else {
		dodaj(a, b, 2 * v, x);
		dodaj(a, b, 2 * v + 1, x);	
	}
	if (tree[v].warstwy > 0) {
		tree[v].ilosc = tree[v].kon - tree[v].pocz + 1;
	} else if (2 * v < 2 * R) {
		tree[v].ilosc = tree[2 * v].ilosc + tree[2 * v + 1].ilosc;
	} else {
		tree[v].ilosc = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for(int i = 1; i <= n; i++) {
		int a, b, c, d, e, f;
		cin >> a >> b >> c >> d >> e >> f;
		wej[i] = {{a, b, c}, {d + 1, e + 1, f}};
	}
	
	for (int i = R; i < 2 * R; i++) {
		tree[i].pocz = i - R;
		tree[i].kon = i - R;
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i].pocz = tree[2 * i].pocz;
		tree[i].kon = tree[2 * i + 1].kon;
	}
	
	for (int z = 1; z <= MAX_Z; z++) {
		for (int i = 1; i < 2 * R; i++) {
			tree[i].ilosc = 0;
			tree[i].warstwy = 0;
		}
		
		int indeks = 0;
		ll spodziewane_pole = 0;
		for (int i = 1; i <= n; i++) {
			Klocek klocek = wej[i];
			if (na_poziomie(klocek, z)) {
				brzegi[indeks++] = {klocek.a.x, klocek.b.x, klocek.a.y, true};
				brzegi[indeks++] = {klocek.a.x, klocek.b.x, klocek.b.y, false};
				
				spodziewane_pole += (klocek.b.x - klocek.a.x) * (klocek.b.y - klocek.a.y);
			}
		}
		if (indeks == 0) continue;
		
		sort(brzegi, brzegi + indeks, [](Brzeg& a, Brzeg& b) { return a.y == b.y ? b.czy_pocz : a.y < b.y; });
		
		ll pole = 0;
		dodaj(brzegi[0].x1, brzegi[0].x2 - 1, 1, brzegi[0].czy_pocz ? 1 : -1);
		for (int i = 1; i < indeks; i++) {
			ll wysokosc = brzegi[i].y - brzegi[i - 1].y;
			ll szerokosc = tree[1].ilosc;
			pole += wysokosc * szerokosc;
			dodaj(brzegi[i].x1, brzegi[i].x2 - 1, 1, brzegi[i].czy_pocz ? 1 : -1);
		}
		
		if (pole != spodziewane_pole) {
			cout << "TAK";
			return 0;
		}
	}

	cout << "NIE";

	return 0;
}