#include "loc_lib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = (1 << 20);
int akt[MAX + 10];
int nowe[MAX + 10];

int rozwiaz_pare(int a, int b) {
	return (pytanie(a, b) == '>' ? a : b);
}

int rozwiaz_cztery(int a, int b, int c, int d) {
	char odp = pytanie(a, d);
	if (odp == '=') {
		return rozwiaz_pare(b, c);
	} else if (odp == '>') {
		return rozwiaz_pare(a, c);
	} else {
		return rozwiaz_pare(b, d);
	}
}

int zmiejsz(int rozmiar) {
	int nowy_rozmiar = 0;
	for (int i = 1; i <= rozmiar; i += 4) {
		if (i + 3 <= rozmiar) {
			nowe[++nowy_rozmiar] = rozwiaz_cztery(akt[i], akt[i + 1], akt[i + 2], akt[i + 3]);
		} else {
			nowe[++nowy_rozmiar] = rozwiaz_pare(akt[i], akt[i + 1]);
		}
	}
	for (int i = 1; i <= nowy_rozmiar; i++) {
		akt[i] = nowe[i];
	}
	return nowy_rozmiar;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n = daj_n();
	
	if (n == 0) {
		odpowiedz(1);
		return 0;
	}
	
	if (n == 1) {
		odpowiedz(rozwiaz_pare(1, 2));
		return 0;
	}
	
	if (n == 2) {
		odpowiedz(rozwiaz_cztery(1, 2, 3, 4));
		return 0;
	}
	
	if (n == 3) {
		int a = rozwiaz_cztery(1, 2, 3, 4);
		int b = rozwiaz_cztery(5, 6, 7, 8);
		odpowiedz(rozwiaz_pare(a, b));
		return 0;
	}
	
	if (n == 4) {
		int wyniki[4];
		for (int i = 0; i < 4; i++) {
			wyniki[i] = rozwiaz_cztery(4 * i + 1, 4 * i + 2, 4 * i + 3, 4 * i + 4);
		}
		odpowiedz(rozwiaz_cztery(wyniki[0], wyniki[1], wyniki[2], wyniki[3]));
		return 0;
	}
	
	int rozmiar = (1 << n);
	for (int i = 1; i <= rozmiar; i++) {
		akt[i] = i;
	}
	
	while (rozmiar > 1) {
		rozmiar = zmiejsz(rozmiar);
	}
	odpowiedz(akt[1]);

	return 0;
}
