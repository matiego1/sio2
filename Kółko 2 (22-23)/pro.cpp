#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Przedzial {
	int pocz, kon, warstwy, ilosc;
};
struct Brzeg {
	int x1, x2, y;
	bool czy_pocz;
};

const int MAX = 100 * 1000;
const int R = (1 << 18);
Przedzial tree[2 * R];
Brzeg brzegi[2 * MAX + 1];
set<int> pozX;

void dodaj(int a, int b, int v, int x) {
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
	
	for (int i = 1; i <= n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;

		brzegi[2 * i - 1] = {a, c, b, true};
		brzegi[2 * i] = {a, c, d, false};
		
		pozX.insert(a);
		pozX.insert(c);
	}
	
	auto it = pozX.begin();
	int indeks = R, pop = *(it++);
	for (; it != pozX.end(); it++) {
		tree[indeks].pocz = pop;	
		tree[indeks].kon = *it - 1;
		pop = *it;
		indeks++;
	}
	while (indeks < 2 * R) {
		tree[indeks].pocz = pop;
		tree[indeks].kon = pop;
		indeks++;
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i].pocz = tree[2 * i].pocz;
		tree[i].kon = tree[2 * i + 1].kon;
	}
	
	sort(brzegi + 1, brzegi + 1 + n + n, [](Brzeg& a, Brzeg& b) { return a.y < b.y; });
	
	ll wynik = 0;
	dodaj(brzegi[1].x1, brzegi[1].x2 - 1, 1, brzegi[1].czy_pocz ? 1 : -1);
	for (int i = 2; i <= 2 * n; i++) {
		ll wysokosc = brzegi[i].y - brzegi[i - 1].y;
		ll szerokosc = tree[1].ilosc;
		wynik += wysokosc * szerokosc;
		dodaj(brzegi[i].x1, brzegi[i].x2 - 1, 1, brzegi[i].czy_pocz ? 1 : -1);
	}
	
	cout << wynik;
	
	return 0;
}
