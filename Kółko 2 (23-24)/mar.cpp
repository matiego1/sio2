#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, int> para;

struct Node {
	ll wart, indeks;
	ll zepchnij;
};

const ll INF = 9223372036854775807ll;
const int R = (1 << 18);
const int POCZ = R;
const int KON = 2 * R - 1;
const int MAX = 200 * 1000;
Node tree[2][2 * R];
int biezaca_klasa[MAX + 1];

void push(int klasa, int v) {
	if (tree[klasa][v].zepchnij != 0) {
		tree[klasa][2 * v].wart += tree[klasa][v].zepchnij;
		tree[klasa][2 * v].zepchnij += tree[klasa][v].zepchnij;
		tree[klasa][2 * v + 1].wart += tree[klasa][v].zepchnij;
		tree[klasa][2 * v + 1].zepchnij += tree[klasa][v].zepchnij;
		tree[klasa][v].zepchnij = 0;
	}
}

void polacz(int klasa, int v) {
	if (tree[klasa][2 * v].wart > tree[klasa][2 * v + 1].wart) {
		tree[klasa][v].wart = tree[klasa][2 * v].wart;
		tree[klasa][v].indeks = tree[klasa][2 * v].indeks;
	} else {
		tree[klasa][v].wart = tree[klasa][2 * v + 1].wart;
		tree[klasa][v].indeks = tree[klasa][2 * v + 1].indeks;
	}
}

void add(int klasa, int a, int b, int l, int r, int v, ll x) {
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		tree[klasa][v].wart += x;
		tree[klasa][v].zepchnij += x;
	} else {
		push(klasa, v);
		add(klasa, a, b, l, (l + r) / 2, 2 * v, x);
		add(klasa, a, b, (l + r) / 2 + 1, r, 2 * v + 1, x);
		polacz(klasa, v);
	}
}

void reset(int klasa, int v) {
	v += R;
	add(klasa, v, v, POCZ, KON, 1, -1000ll * 1000 * 1000 * 1000 * 1000 * 1000);
}

para query(int klasa) {
	return {tree[klasa][1].wart, tree[klasa][1].indeks};
}

int wczytaj_int() {
	int x = 0, znak;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = x * 10 + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj_int(), m = wczytaj_int(), g2 = wczytaj_int(), g1 = wczytaj_int();
	
	for (int i = 0; i < 2 * R; i++) {
		tree[0][i].wart = -INF;
		tree[1][i].wart = -INF;
	}
	
	for (int i = 1; i <= n; i++) {
		int a = wczytaj_int();
		tree[0][R + i].wart = a;
		tree[1][R + i].wart = a;
		tree[0][R + i].indeks = i;
		tree[1][R + i].indeks = i;
	}
	for (int i = R - 1; i >= 1; i--) {
		polacz(0, i);
		polacz(1, i);
	}
	
	int wynik1 = 0, wynik2 = 0;
	
	while (m--) {
		int a = wczytaj_int(), b = wczytaj_int(), x = wczytaj_int();
		
		g1 = max(0, g1 - 1);
		g2 = max(0, g2 - 1);

		if (a == 1 && b == n) {
			g1 = max(0, g1 - x);
			g2 = max(0, g2 - x);
		} else if (x > 0) {
			add(0, R + a, R + b, POCZ, KON, 1, x);
			add(1, R + a, R + b, POCZ, KON, 1, x);
		}
		
		para p;
		while ((p = query(0)).first >= g1 && p.first > 0) {
			if (biezaca_klasa[p.second] == 2) {
				wynik2--;
			}
			biezaca_klasa[p.second] = 1;
			wynik1++;
			reset(0, p.second);
			reset(1, p.second);
		}

		while ((p = query(1)).first >= g2 && p.first > 0) {
			biezaca_klasa[p.second] = 2;
			wynik2++;
			reset(1, p.second);
		}
		
		printf("%d %d\n", wynik1, wynik2);
	}

	return 0;
}
