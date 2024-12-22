#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
const ll MOD = 1000 * 1000 * 1000 + 7;
const ll P = 29;
bool sito[MAX + 1];
int dzielnik[MAX + 1];
ll pref[MAX + 1];
ll potegi[MAX + 1];

void generuj_sito(int maks) {
	for (int i = 2; i <= maks; i++) {
		sito[i] = true;
		dzielnik[i] = i;
	}
	for (int i = 2; i * i <= maks; i++) {
		if (!sito[i]) continue;
		dzielnik[i] = i;
		for (int j = i * i; j <= maks; j += i) {
			sito[j] = false;
			dzielnik[j] = i;
		}
	}
}

para znajdz_czynnik(int x) {
	int czynnik = dzielnik[x];
	int wynik = czynnik;
	while (x % (wynik * czynnik) == 0) wynik *= czynnik;
	return {czynnik, wynik};
}

ll hash_pref(int pocz, int kon) {
	return (pref[kon] - (pref[pocz - 1] * potegi[kon - pocz + 1] % MOD) + MOD) % MOD;
}

bool czy_okres(int pocz, int kon, int k) {
	int n = kon - pocz + 1;
	if (k > n) return false;
	if (k == n) return true;
	return hash_pref(pocz, kon - k) == hash_pref(pocz + k, kon);
}

int rozwiaz(int pocz, int kon) {
	int iloczyn = 1, n = kon - pocz + 1;
	while (n != iloczyn) {
		para k = znajdz_czynnik(n / iloczyn);
		if (czy_okres(pocz, kon, n / k.first)) {
			n /= k.first;
			kon = n + pocz - 1;
		} else {
			iloczyn *= k.second;
		}
	}
	return n;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	potegi[0] = 1;
	for (int i = 1; i <= n; i++) {
		potegi[i] = potegi[i - 1] * P % MOD;
	}
	generuj_sito(n);
	
	string s;
	cin >> s;
	s = "$" + s;
	
	for (int i = 1; i <= n; i++) {
		pref[i] = (pref[i - 1] * P + s[i] - 'a') % MOD;
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << rozwiaz(a, b) << "\n";
	}
	

	return 0;
}

