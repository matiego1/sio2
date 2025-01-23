#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 10 * 1000;
int dp[MAX + 1][MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		
		for (int s = 1; s < min(x, MAX + 1); s++) {
			dp[i][s] = dp[i - 1][s];
		}
		
		if (x <= MAX) dp[i][x] = i;
		for (int s = x + 1; s <= MAX; s++) {
			dp[i][s] = max(dp[i - 1][s], dp[i - 1][s - x]);
		}
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int pocz, kon, s;
		cin >> pocz >> kon >> s;
		
		if (dp[kon][s] >= pocz) {
			cout << "TAK\n";
		} else {
			cout << "NIE\n";
		}
	}

	return 0;
}

