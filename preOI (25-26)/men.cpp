#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	ll dp1 = 0, dp1i = 0;
	ll dp2 = 0, dp2i = 0;
	for (int i = 1; i <= n; i++) {
		int o, smak;
		cin >> o >> smak;
		
		ll maks = dp1;
		if (dp1i == o) {
			maks = dp2;
		}
		
		ll nowa = maks + smak;
		
		if (dp1i == o) {
			dp1 = max(dp1, nowa);
		} else if (dp2i == o) {
			dp2 = max(dp2, nowa);
		} else if (nowa > dp1) {
			dp2 = dp1;
			dp2i = dp1i;
			dp1 = nowa;
			dp1i = o;
		} else if (nowa > dp2) {
			dp2 = nowa;
			dp2i = o;
		}
		
		if (dp2 > dp1) {
			swap(dp1, dp2);
			swap(dp1i, dp2i);
		}
	}
	
	cout << dp1;

	return 0;
}

