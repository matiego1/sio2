#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

const ll MAX_A = 10ll * 1000 * 1000 * 1000;
const int sqrt_MAX_A = 100 * 1000;
const int MAX = 2153; //ile x, ze 1 <= x ** 3 <= 10 ** 10
map<ll, int> mapa;

bool sito[MAX + 1];
vector<int> pierwsze;
vector<int> pierwsze2;
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
			pierwsze2.push_back(i * i);
		}
	}
}

int pierwiastek(ll x) {
	int pocz = 1, kon = sqrt_MAX_A;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (srodek * srodek < x) {
			pocz = srodek + 1;
		} else {
			kon = srodek;
		}
	}
	return ((ll) pocz * pocz == x ? pocz : 0);
}

int rozloz(ll x) {
	ll rozklad = 1, brakuje = 1;
	for (int i = 0; i < pierwsze.size(); i++) {
		int ilosc = 0;
		while (x % pierwsze[i] == 0) {
			x /= pierwsze[i];
			ilosc++;
		}
		
		ilosc %= 3;
		if (ilosc == 1) {
			rozklad *= pierwsze[i];
			brakuje *= pierwsze2[i];
		} else if (ilosc == 2) {
			rozklad *= pierwsze2[i];
			brakuje *= pierwsze[i];
		}
		if (brakuje > MAX_A) return 0;
	}
	
	int pier = pierwiastek(x);
	if (pier > 0) {
		int wynik = mapa[pier * brakuje];
		mapa[x * rozklad]++;
		return wynik;
	}
	
	if (x > sqrt_MAX_A || x * brakuje > MAX_A) return 0;
	int wynik = mapa[x * x * brakuje];
	mapa[x * rozklad]++;
	return wynik;
}

int main() {
	int n;
	scanf("%d", &n);
	
	wygeneruj_pierwsze();

	ll wynik = 0;	
	for (int i = 1; i <= n; i++) {
		ll x;
		scanf("%lld", &x);
		
		wynik += rozloz(x);
	}
		
	printf("%lld", wynik);
	return 0;
}
