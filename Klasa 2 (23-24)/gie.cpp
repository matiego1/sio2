#include <iostream>
using namespace std;
typedef long long ll;

const int MAX_N = 10 * 1000;
const int MAX_K = 1000;
int wej[MAX_N + 1];
ll dp[2 * MAX_K + 1][MAX_N + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	for (int i = 1; i <= 2 * k; i++) {
		if (i % 2 == 0) {
			dp[i][0] = dp[i - 1][0] + wej[1];
		} else {
			dp[i][0] = dp[i - 1][0] - wej[1];
		}
		for (int j = 2; j <= n; j++) {
			if (i % 2 == 0) {
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j] + wej[j]);
			} else {
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j] - wej[j]);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 2 * k; j++) {
			if (j % 2 == 0) {
				dp[j][i] = max(dp[j][i - 1], dp[j - 1][i] + wej[i]);
			} else {
				dp[j][i] = max(dp[j][i - 1], dp[j - 1][i] - wej[i]);
			}
		}
	}
	
	cout << dp[2 * k][n];

	return 0;
}

