#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 2000;
int A[MAX + 1];
int B[MAX + 1];
int dp[MAX + 1][MAX + 1][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> B[i];
	}
	
	for (int j = 0; j <= m; j++) {
		for (int i = 0; i <= n; i++) {
			if (i == 0 && j == 0) continue;
			
			dp[i][j][0] = INT_MIN;
			if (i > 0) dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][1] + A[i]);
			if (j > 0) dp[i][j][0] = max(dp[i][j][0], dp[i][j - 1][1] + B[j]);
			dp[i][j][1] = INT_MAX;
			if (i > 0) dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][0]);
			if (j > 0) dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0]);
		}
	}
	
	cout << dp[n][m][0];

	return 0;
}

