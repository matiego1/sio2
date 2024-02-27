#include <iostream>
using namespace std;

const int MAX = 500 * 1000;
int wej[MAX + 1];
int dp[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
    }

    dp[1] = 9;
    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 1] + wej[i], dp[i - 2] + wej[i - 1] + 9);
    }

    cout << dp[n];

    return 0;
}
