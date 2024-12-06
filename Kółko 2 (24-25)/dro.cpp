#include <iostream>
using namespace std;

const int MAX = 1000;
const int MOD = 1000 * 1000;
long long wej[2][MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    wej[1][1] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;

            if (i == 1 && j == 1) continue;

            if (a == 0) {
                wej[i % 2][j] = (wej[(i - 1) % 2][j] + wej[i % 2][j - 1]) % MOD;
            } else {
                wej[i % 2][j] = 0;
            }
        }
    }

    cout << wej[n % 2][n] % MOD;
    return 0;
}