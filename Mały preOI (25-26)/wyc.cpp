#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Wart {
	int lewy, dlug_lewy;
	int prawy, dlug_prawy;
	ll wynik;
	int rozmiar;
};

const int MAX = 200 * 1000;
const int R = (1 << 18);
int wej[MAX + 1];
Wart tree[2 * R];

ll mozliwosci(ll dlug) {
	return dlug * (dlug + 1) / 2;
}

Wart polacz(Wart& lewy, Wart& prawy) {
	if (lewy.prawy > prawy.lewy) {
		return {lewy.lewy, lewy.dlug_lewy, prawy.prawy, prawy.dlug_prawy, lewy.wynik + prawy.wynik, lewy.rozmiar + prawy.rozmiar};
	} else {
		ll wynik = lewy.wynik - mozliwosci(lewy.dlug_prawy);
		wynik += prawy.wynik - mozliwosci(prawy.dlug_lewy);
		wynik += mozliwosci(lewy.dlug_prawy + prawy.dlug_lewy);
		
		int dlug_lewy = lewy.dlug_lewy;
		if (lewy.dlug_lewy == lewy.rozmiar) {
			dlug_lewy += prawy.dlug_lewy;
		}
		
		int dlug_prawy = prawy.dlug_prawy;
		if (prawy.dlug_prawy == prawy.rozmiar) {
			dlug_prawy += lewy.dlug_prawy;
		}
		
		return {lewy.lewy, dlug_lewy, prawy.prawy, dlug_prawy, wynik, lewy.rozmiar + prawy.rozmiar};
	}
}

void ustaw(int v, int wart) {
	v += R;
	tree[v] = {wart, 1, wart, 1, 1, 1};
	
	while (v > 1) {
		v /= 2;
		tree[v] = polacz(tree[2 * v], tree[2 * v + 1]);
	}
}

ll query(int l, int r) {
	l += R;
	r += R;
	
	if (l == r) {
		return tree[l].wynik;
	}
	
	Wart lewy = tree[l];
	Wart prawy = tree[r];
	
	while (l / 2 != r / 2) {
		if (l % 2 == 0) {
			lewy = polacz(lewy, tree[l + 1]);
		}
		if (r % 2 == 1) {
			prawy = polacz(tree[r - 1], prawy);
		}
		l /= 2;
		r /= 2;
	}
	
	return polacz(lewy, prawy).wynik;
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), q = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		int a = wczytaj();
		tree[i + R] = {a, 1, a, 1, 1, 1};
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = polacz(tree[2 * i], tree[2 * i + 1]);
	}
	
	while (q--) {
		int t = wczytaj();
		if (t == 1) {
			int x = wczytaj(), y = wczytaj();
			
			ustaw(x, y);
		} else {
			int l = wczytaj(), r = wczytaj();
			
			printf("%lld\n", query(l, r));
		}
	}

	return 0;
}
