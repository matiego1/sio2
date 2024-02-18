#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int MAX = 100 * 1000;
const ll P1 = 15671;
const ll MOD1 = 1000 * 1000 * 1000 + 7;
const ll P2 = 45377;
const ll MOD2 = 1000012309;
ll potega_p1[MAX + 1];
ll potega_p2[MAX + 1];

int n;
string s1, s2;

set<para> fragmenty;

bool sprawdz(int m) {
	fragmenty.clear();
	
	ll hash1 = 0, hash2 = 0;
	for (int i = 0; i < m; i++) {
		hash1 = (hash1 * P1 + s1[i]) % MOD1;
		hash2 = (hash2 * P2 + s1[i]) % MOD2;
	}
	fragmenty.insert(make_pair(hash1, hash2));
	
	for (int i = m; i < n; i++) {
		hash1 = (hash1 - (s1[i - m] * potega_p1[m - 1]) % MOD1 + MOD1) % MOD1;
		hash1 = (hash1 * P1 + s1[i]) % MOD1;
		
		hash2 = (hash2 - (s1[i - m] * potega_p2[m - 1]) % MOD2 + MOD2) % MOD2;
		hash2 = (hash2 * P2 + s1[i]) % MOD2;
		
		fragmenty.insert(make_pair(hash1, hash2));
	}
	
	hash1 = 0;
	hash2 = 0;
	for (int i = 0; i < m; i++) {
		hash1 = (hash1 * P1 + s2[i]) % MOD1;
		hash2 = (hash2 * P2 + s2[i]) % MOD2;
	}
	if (fragmenty.find(make_pair(hash1, hash2)) != fragmenty.end()) {
		return true;
	}
	
	for (int i = m; i < n; i++) {
		hash1 = (hash1 - (s2[i - m] * potega_p1[m - 1]) % MOD1 + MOD1) % MOD1;
		hash1 = (hash1 * P1 + s2[i]) % MOD1;
		
		hash2 = (hash2 - (s2[i - m] * potega_p2[m - 1]) % MOD2 + MOD2) % MOD2;
		hash2 = (hash2 * P2 + s2[i]) % MOD2;
		
		if (fragmenty.find(make_pair(hash1, hash2)) != fragmenty.end()) {
			return true;
		}
	}
	
	return false;
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
	
	cin >> n;
	cin >> s1;
	s2 = s1;
	reverse(s2.begin(), s2.end());
	
	int pocz = 1, kon = n;
	while (pocz < kon) {
		int srodek = (pocz + kon + 1) / 2;
		if (sprawdz(srodek)) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
		}
	}
	
	cout << pocz;

	return 0;
}

