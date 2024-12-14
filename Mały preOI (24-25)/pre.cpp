#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll MOD = 998244353;

ll log2(ll x) {
	return 63 - __builtin_clzll(x);
}

void rozwiaz() {
	ll p, k;
	cin >> p >> k;
	
	ll w = log2(k / p);
	cout << w + 1 << " ";
	
	ll wynik = (k / (1ll << w) - p + 1) % MOD;
	
	if (p * 3 * (1ll << (w - 1)) <= k) {
		ll akt = k / 3 / (1ll << (w - 1)) - p + 1;
		akt = akt * w % MOD;
		wynik = (wynik + akt) % MOD;
	}
	cout << wynik << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	while (n--) {
		rozwiaz();
	}

	return 0;
}

