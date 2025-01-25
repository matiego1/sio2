#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

ll ceil(ll a, ll b) {
	if (a % b == 0) return a / b;
	return a / b + 1;
}

ll rozwiaz(ll l, ll r) {
	ll pocz = l + 1;
	ll kon = r + 1;
	
	if (pocz <= 0 && 0 <= kon) return -1;
	
	if (pocz < 0 && kon < 0) {
		swap(pocz, kon);
		pocz *= -1;
		kon *= -1;
	}
	
	ll R = 0;
	for (ll y1 = 1; y1 * y1 <= kon; y1++) {
		R += (kon / y1) - max(ceil(pocz, y1), y1) + 1;
	}
	
	if (l >= 0 && r >= 0) {
		return 2 * R;
	}
	
	ll S = 0;
	for (ll i = 1; i * i <= kon; i++) {
		if (pocz <= i * i) S++;
	}
	
	return 2 * R - S;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int q;
	cin >> q;
	
	while (q--) {
		ll l, r;
		cin >> l >> r;
		cout << rozwiaz(l, r) << "\n";
	}

	return 0;
}
