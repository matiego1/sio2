#include <iostream>
using namespace std;
typedef long long ll;

const int R = 4;
const int MOD = 1000 * 1000 * 1000 + 7;

void pomnoz(ll m1[R], ll m2[R][R]) {
	ll wynik[R];
	for (int i = 0; i < R; i++) {
		wynik[i] = 0;
		for (int j = 0; j < R; j++) {
			wynik[i] = (wynik[i] + ((m1[j] * m2[i][j]) % MOD)) % MOD;
		}
	}
	for (int i = 0; i < R; i++ ){
		m1[i] = wynik[i];
	}
}

void kwadrat(ll m[R][R]) {
	ll wynik[R][R];
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < R; j++) {
			wynik[i][j] = 0;
			for (int k = 0; k < R; k++) {
				wynik[i][j] = (wynik[i][j] + ((m[i][k] * m[k][j]) % MOD)) % MOD;
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < R; j++) {
			m[i][j] = wynik[i][j];
		}
	}
}


ll suma(ll x) {
	if (x == 0) return 0;
	x--;
	
	ll macierz[4][4] = {
		{1, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 1, 1, 2},
		{0, 0, 1, 1}
	};
	ll wynik[4] = {1, 1, 4, 2};
	
	while (x > 0) {
		if (x % 2 == 1) {
			pomnoz(wynik, macierz);
		}
		kwadrat(macierz);
		x /= 2;
	}
	
	return wynik[0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll a, b;
	cin >> a >> b;	
	cout << (suma(b) - suma(a - 1) + MOD) % MOD;

	return 0;
}

