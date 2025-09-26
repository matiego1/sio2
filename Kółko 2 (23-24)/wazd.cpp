#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000;
int wej[MAX + 1][2];
ll dp[MAX + 1][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			cin >> wej[x][y % 2];
			
			dp[x][y % 2] = LLONG_MIN;
			if (y > 1) {
				dp[x][y % 2] = max(dp[x][y % 2], wej[x][y % 2] + dp[x][(y - 1) % 2]);
			}
			if (x > 1) {
				dp[x][y % 2] = max(dp[x][y % 2], wej[x][y % 2] + dp[x - 1][y % 2]);
			}
			if (x == 1 && y == 1) {
				dp[x][y % 2] = wej[x][y % 2];
			}
		}
	}
	
	cout << dp[m][n % 2];

	return 0;
}

