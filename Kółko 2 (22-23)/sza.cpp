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
para pref[MAX + 1];

int n;
vector<int> kandydaci;

para hash_pref(int a, int b) {	
	ll hash1 = (pref[b].first - ((pref[a - 1].first * potega_p1[b - a + 1]) % MOD1) + MOD1) % MOD1;
	ll hash2 = (pref[b].second - ((pref[a - 1].second * potega_p2[b - a + 1]) % MOD2) + MOD2) % MOD2;
	return make_pair(hash1, hash2);
}

bool sprawdz(int x) {
	para hash = hash_pref(1, x);
	int koniec = 0;
	for (int i = 1; i + x - 1 <= n; i++) {
		if (hash_pref(i, i + x - 1) == hash) {
			if (i - 1 > koniec) return false;
			koniec = i + x - 1;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	potega_p1[0] = 1;
	potega_p2[0] = 1;
	for (int i = 1; i <= MAX; i++) {
		potega_p1[i] = (potega_p1[i - 1] * P1) % MOD1;
		potega_p2[i] = (potega_p2[i - 1] * P2) % MOD2;
	}
	
	string s;
	cin >> s;
	n = s.length();
	
	for (int i = 1; i <= n; i++) {
		pref[i].first = (pref[i - 1].first * P1 + s[i - 1]) % MOD1;
		pref[i].second = (pref[i - 1].second * P2 + s[i - 1]) % MOD2;
	}
	
	for (int i = 1; i <= n; i++) {
		if (hash_pref(1, i) != hash_pref(n - i + 1, n)) continue;
		kandydaci.push_back(i);
	}
	
	if (sprawdz(kandydaci[0])) {
		cout << kandydaci[0];
		return 0;
	}
	int wynik = kandydaci[0];
	for (int kandydat : kandydaci) {
		if (2 * wynik >= kandydat) continue;
		if (sprawdz(kandydat)) {
			cout << kandydat;
			return 0;
		}
		wynik = kandydat;
	}

	return 0;
}

