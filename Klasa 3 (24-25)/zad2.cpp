#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const ll MOD = 1000 * 1000 * 1000 + 7;
const ll P = 29;
ll potegi_P[MAX + 1];
ll pref[MAX + 1];
vector<int> wynik;

ll suma_pref(ll pocz, ll kon) {
	return (pref[kon] - (pref[pocz - 1] * potegi_P[kon - pocz + 1] % MOD) + MOD) % MOD;
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	potegi_P[0] = 1;
	for (int i = 1; i <= MAX; i++) {
		potegi_P[i] = potegi_P[i - 1] * P % MOD;
	}

	string a, b;
	cin >> a >> b;
	int n = (int) a.length(), m = (int) b.length();
	a = "$" + a;
	b = "$" + b;
	
	ll wzor = 0;
	for (int i = 1; i <= n; i++) {
		wzor = (wzor * P + a[i] - 'a') % MOD;
	}
	
	for (int i = 1; i <= m; i++) {
		pref[i] = (pref[i - 1] * P + b[i] - 'a') % MOD;
	}
	
	for (int i = 1; i + n - 1 <= m; i++) {
		if (suma_pref(i, i + n - 1) == wzor) {
			wynik.push_back(i);
		}
	}
	
	cout << wynik.size() << "\n";
	for (int i : wynik) cout << i << " ";

	return 0;
}

