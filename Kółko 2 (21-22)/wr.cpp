#include <iostream>
#include <vector>
using namespace std;

const int INF = 2 * 1000 * 1000 * 1000;
vector<vector<int>> dp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int k, n;
    cin >> k >> n;

    dp.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i].resize(k + 1);
    }

    for (int i = 1; i <= k; i++) {
        dp[0][i] = INF;
    }

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        for (int j = 1; j <= k; j++) {
            if (x == j) {
                dp[i][j] = 1;
            } else if (x > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = min(dp[i - 1][j], 1 + dp[i][j - x]);
            }
        }
    }

    if (dp[n][k] == INF) {
        cout << "NIE";
    } else {
        cout << dp[n][k];
    }

    return 0;
}
