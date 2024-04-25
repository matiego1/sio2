#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll MOD = 1000 * 1000 * 1000 + 7;
const ll P = 31;
const int MAX = 200 * 1000;
ll potegi[MAX + 1];
ll pref[MAX + 1];
string s;

ll hash_pref(int l, int r) {
    return (pref[r] - ((pref[l - 1] * potegi[r - l + 1]) % MOD) + MOD) % MOD;
}

int sprawdz(int a, int b, int l) {
	if (hash_pref(a, a + l - 1) == hash_pref(b, b + l - 1)) return 0;
	return (s[a + l - 1] > s[b + l - 1] ? 1 : -1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	potegi[0] = 1;
	for (int i = 1; i <= MAX; i++) {
		potegi[i] = (potegi[i - 1] * P) % MOD;
	}
	
	cin >> s;
	s = "$" + s;
	
	for (int i = 1; i <= (int) s.length(); i++) {
		pref[i] = (pref[i - 1] * P + s[i]) % MOD;
	}
	
	int m;
	cin >> m;
	
	while (m--) {
		int a, b, l;
		cin >> a >> b >> l;
		
		int pocz = 1, kon = l;
		while (pocz < kon) {
			int srodek = (pocz + kon) / 2;
			if (sprawdz(a, b, srodek) == 0) {
				pocz = srodek + 1;
			} else {
				kon = srodek;
			}
		}
		
		int x = sprawdz(a, b, pocz);
		if (x == 0) {
			cout << "=\n";
		} else if (x > 0) {
			cout << ">\n";
		} else {
			cout << "<\n";
		}
	}

	return 0;
}


