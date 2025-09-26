#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> para;

const ull MOD = 1000 * 1000 * 1000;
const int MAX_K = 13;
ull symbol_newtona[MAX_K + 1][MAX_K + 1] = {{1,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,2,1,0,0,0,0,0,0,0,0,0,0,0},{1,3,3,1,0,0,0,0,0,0,0,0,0,0},{1,4,6,4,1,0,0,0,0,0,0,0,0,0},{1,5,10,10,5,1,0,0,0,0,0,0,0,0},{1,6,15,20,15,6,1,0,0,0,0,0,0,0},{1,7,21,35,35,21,7,1,0,0,0,0,0,0},{1,8,28,56,70,56,28,8,1,0,0,0,0,0},{1,9,36,84,126,126,84,36,9,1,0,0,0,0},{1,10,45,120,210,252,210,120,45,10,1,0,0,0},{1,11,55,165,330,462,462,330,165,55,11,1,0,0},{1,12,66,220,495,792,924,792,495,220,66,12,1,0},{1,13,78,286,715,1287,1716,1716,1287,715,286,78,13,1}};

ull tab[MAX_K + 2];
ull macierz[MAX_K + 2][MAX_K + 2];
ull pom[MAX_K + 2][MAX_K + 2];

void pomnoz(int R) {
	for (int k = 0; k < R; k++) {
		for (int j = 0; j < R; j++) {
			pom[0][j] = (pom[0][j] + ((tab[k] * macierz[k][j]) % MOD)) % MOD;
		}
	}
	for (int j = 0; j < R; j++) {
		tab[j] = pom[0][j];
		pom[0][j] = 0;
	}
}

void kwadrat(int R) {
	for (int i = 0; i < R; i++) {
		for (int k = 0; k < R; k++) {
			for (int j = 0; j < R; j++) {
				pom[i][j] = (pom[i][j] + ((macierz[i][k] * macierz[k][j]) % MOD)) % MOD;
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < R; j++) {
			macierz[i][j] = pom[i][j];
			pom[i][j] = 0;
		}
	}
}

ll policz(int k, ull n) {
	for (int i = 0; i < MAX_K + 2; i++) {
		tab[i] = (1 << k);
	}
	
	for (int i = 0; i < k + 2; i++) {
		for (int j = 0; j < k + 2; j++) {
			macierz[i][j] = 0;
		}
	}
	
	macierz[0][0] = 1;
	macierz[1][0] = 1;
	int indeks = 1;
	for (int p = k; p >= 0; p--) {
		for (int r = 0; r <= p; r++) {
			macierz[r + 1][indeks] = symbol_newtona[p][r];
		}
		indeks++;
	}
	
	while (n) {
		if (n & 1) {
			pomnoz(k + 2);
		}
		kwadrat(k + 2);
		n /= 2;
	}
	
	return tab[0];
}

int main() {
	ull n;
	int k;
	scanf("%llu %d", &n, &k);
	
	ull wynik = 0;
	
	for (int j = 0; j <= k; j++) {
		ull akt = symbol_newtona[k][j];
		akt = (akt * policz(j, n)) % MOD;
		if ((k - j) & 1) {
			wynik = (wynik - akt + MOD) % MOD;
		} else {
			wynik = (wynik + akt) % MOD;
		}
	}
	
	printf("%09llu", wynik % MOD);

	return 0;
}