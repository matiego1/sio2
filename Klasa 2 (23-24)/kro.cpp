#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int wej[MAX + 1];
long long dp[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
        dp[i] = max(dp[i - 1], dp[max(0, i - 2)] + wej[i]);
    }

    cout << dp[n];

    return 0;
}
