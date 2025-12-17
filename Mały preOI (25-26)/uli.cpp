#include "ulilib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

vector<int> tab;
vector<int> akt;

int n, x, y;

bool sprawdz(int pocz, int kon) {
	akt.clear();
	for (int i = pocz; i <= kon; i++) {
		akt.push_back(tab[i]);
	}
	
	int odp = pytaj(akt);
	int reszta = (akt.size() & 1 ? x : 0);
	return ((odp ^ reszta) == (x ^ y));
}

int wyszukaj() {
	int pocz = 0, kon = (int) tab.size() - 1;
	while (pocz < kon) {
		int srodek = (pocz + kon) / 2;
		
		if (sprawdz(pocz, srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	return tab[pocz];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	init(n, x, y);
	
	int roznica = 0, rozny_bit = -1;
	for (int bit = 0; bit <= 9; bit++) {
		tab.clear();
		for (int i = 1; i <= n; i++) {
			if ((1 << bit) & i) {
				tab.push_back(i);
			}
		}
		
		if (tab.empty()) continue;
		
		int odp = pytaj(tab);
		int reszta = (tab.size() & 1 ? x : 0);
		if ((odp ^ reszta) == (x ^ y)) {
			roznica |= (1 << bit);
			if (rozny_bit == -1) rozny_bit = bit;
		}
	}
	
	tab.clear();
	for (int i = 1; i <= n; i++) {
		if ((1 << rozny_bit) & i) {
			tab.push_back(i);
		}
	}
	
	int p1 = wyszukaj();
	int p2 = p1 ^ roznica;
	
	if (p1 > p2) swap(p1, p2);
	odpowiedz(p1, p2);

	return 0;
}

