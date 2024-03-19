#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
const ll P = 997;
const ll MOD = 1000 * 1000 * 1000 + 7;

ll potega_p[MAX + 1];
int ps[2 * MAX + 10];
ll pref[MAX + 1];

ll hash_pref(int a, int b) {
	return (pref[b] - ((pref[a - 1] * potega_p[b - a + 1]) % MOD) + MOD) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	potega_p[0] = 1;
	for (int i = 1; i <= MAX; i++) {
		potega_p[i] = (potega_p[i - 1] * P) % MOD;
	}

	string t, s;
	cin >> t >> s;
	
	string kmp = "$" + s + "$" + t;
	
	ps[0] = -1;
	ps[1] = 0;
	for (int i = 2; i < (int) kmp.length(); i++) {
		int wyn = ps[i - 1];
		while (wyn >= 0 && kmp[i] != kmp[wyn + 1]) {
			wyn = ps[wyn];
		}
		ps[i] = wyn + 1;
	}
	
	for (int i = 1; i < (int) kmp.length(); i++) {
		pref[i] = (pref[i - 1] * P) % MOD;
		pref[i] = (pref[i] + kmp[i]) % MOD;
	}
	
	for (int i = (int) s.length() + 2; i < (int) kmp.length(); i++) {
		if (ps[i] <= 0) continue;
		if (i - s.length() + 1 < s.length() + 2) continue;
		if (hash_pref(ps[i] + 1, (int) s.length()) != hash_pref(i - (int) s.length() + 1, i - ps[i])) continue;
		cout << "TAK";
		return 0;
	}

	cout << "NIE";
	return 0;
}


