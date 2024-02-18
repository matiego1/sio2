#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int MAX = 1000 * 1000;
const ll P1 = 15671;
const ll MOD1 = 1000 * 1000 * 1000 + 7;
const ll P2 = 45377;
const ll MOD2 = 1000012309;
ll potega_p1[MAX + 1];
ll potega_p2[MAX + 1];

int n;
string s;
int wszystko_to_samo = 0;
para pref[MAX + 1];
vector<bool> akt;
bool poprawne[MAX + 1];

para hash_pref(int a, int b) {
	ll hash1 = (pref[b].first - ((pref[a - 1].first * potega_p1[b - a + 1]) % MOD1) + MOD1) % MOD1;
	ll hash2 = (pref[b].second - ((pref[a - 1].second * potega_p2[b - a + 1]) % MOD2) + MOD2) % MOD2;
	return make_pair(hash1, hash2);
}

int sprawdz(int m) {
	int indeks = 1;

	para zero = hash_pref(indeks, indeks + m - 1);
	indeks += m;
	para jedynka = hash_pref(indeks, indeks + m - 1);
	indeks += m;
	
	if (zero == jedynka && 2 * m <= wszystko_to_samo) return 0;
	
	while (indeks + m - 1 <= n) {
		if (poprawne[(indeks - 1) / m]) {
			if (hash_pref(indeks, indeks + m - 1) != jedynka) {
				return 0;
			}
		} else {
			if (hash_pref(indeks, indeks + m - 1) != zero) {
				return 0;
			}
		}
		indeks += m;
	}
	
	if (indeks > n) return (indeks - 1) / m;
	
	int pocz = 1;
	if (poprawne[(indeks - 1) / m]) {
		pocz += m;
	}
	
	while (indeks <= n) {
		if (s[indeks] != s[pocz]) {
			return 0;
		}
		indeks++;
		pocz++;
	}

	return (indeks - 1) / m + 1;
}

void dopisz(int x, int& pocz) {
	akt.clear();
	while (x > 0) {
		akt.push_back(x % 2);
		x /= 2;
	}
	for (int i = akt.size() - 1; i >= 0 && pocz <= MAX; i--) {
		poprawne[pocz++] = akt[i];
		if (pocz > MAX) return;
	}
}

int main() {
	potega_p1[0] = 1;
	potega_p2[0] = 1;
	for (int i = 1; i <= MAX; i++) {
		potega_p1[i] = (potega_p1[i - 1] * P1) % MOD1;
		potega_p2[i] = (potega_p2[i - 1] * P2) % MOD2;
	}
	
	poprawne[0] = 0;
	int pocz = 1, x = 1;
	while (pocz <= MAX) {
		dopisz(x++, pocz);
	}
	
	cin >> n;
	cin >> s;
	
	s = "$" + s;
	
	char pop = s[1];
	for (int i = 1; i <= n; i++) {
		pref[i].first = (pref[i - 1].first * P1 + s[i]) % MOD1;
		pref[i].second = (pref[i - 1].second * P2 + s[i]) % MOD2;
		
		if (s[i] == pop && wszystko_to_samo + 1 == i) wszystko_to_samo = i;
	}
	
	if (wszystko_to_samo == n) {
		cout << n;
		return 0;
	}
	
	int wynik = 1;
	for (int i = n / 2; i >= 1; i--) {
		wynik = max(wynik, sprawdz(i));
		if (wynik == n) {
			cout << wynik;
			return 0;
		}
	}
	
	cout << wynik;

	return 0;
}