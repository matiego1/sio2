#include <iostream>
#include <climits>
using namespace std;

const int INF = INT_MAX;

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	
	int dp[k + 1];
	dp[0] = 0;
	for (int i = 1; i <= k; i++) {
		dp[i] = INF;
	}
	
	while (n--) {
		int a;
		cin >> a;
		for (int i = a; i <= k; i++) {
			dp[i] = min(dp[i], (dp[i - a] == INF ? INF : dp[i - a] + 1));
		}
	}
	
	if (dp[k] == INF) {
		cout << "NIE";
	} else {
		cout << dp[k];
	}
	return 0;
}