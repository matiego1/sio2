#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> para;

const ull MOD = 1001;
unordered_map<ll, ull> dp;

ll n, d;
ull a, b;

ull f(ll w, ll v) {
	return min((w * b + v * a) % MOD, (w * a + v * b) % MOD);
}

ull policz(ll x) {
	if (x <= 1) return 0;
	auto p = dp.find(x);
	if (p != dp.end()) return p->second;
	
	ull wynik = ULLONG_MAX;
	for (ll i = max(1ll, (x - d) / 2); i <= min(x - 1, (x + d) / 2); i++) {
		ll j = x - i;
		if (abs(i - j) > d) continue;
		wynik = min(wynik, policz(i) + policz(j) + f(i, j));
	}
	
	dp[x] = wynik;
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> d >> a >> b;
	cout << policz(n);

	return 0;
}
