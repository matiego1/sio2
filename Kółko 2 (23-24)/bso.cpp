#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MOD = 1000 * 1000 * 1000 + 7;
const int MAX = 3200;
bool sito[MAX + 1];
vector<int> pierwsze;
map<int, int> akt;
map<int, int> mapa;

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

void wygeneruj_pierwsze() {
	for (int i = 2; i <= MAX; i++) {
		sito[i] = true;
	}
	for (int i = 2; i * i <= MAX; i++) {
		if (sito[i]) {
			for (int j = i * i; j <= MAX; j += i) {
				sito[j] = false;
			}
		}
	}
	for (int i = 2; i <= MAX; i++) {
		if (sito[i]) {
			pierwsze.push_back(i);
		}
	}
}

void rozloz() {
	akt.clear();
	
	int x = wczytaj();
	
	for (int p : pierwsze) {
		if (p * p > x) break;
		while (x % p == 0) {
			akt[p]++;
			x /= p;
		}
	}
	
	if (x > 1) {
		akt[x]++;
	}
	
	for (para p : akt) {
		mapa[p.first] = max(mapa[p.first], p.second);
	}
}

ll pot(ll a, ll b) {
	ll wynik = 1;
	while (b) {
		if (b & 1) {
			wynik = wynik * a % MOD;
		}
		a = a * a % MOD;
		b /= 2;
	}
	return wynik;
}

int main() {
	wygeneruj_pierwsze();

	int n = wczytaj();
	
	while (n--) rozloz();
	
	ll wynik = 1;
	
	for (para p : mapa) {
		ll x = pot(p.first, p.second);
		wynik = wynik * x % MOD;
	}
	
	printf("%lld", wynik);

	return 0;
}

