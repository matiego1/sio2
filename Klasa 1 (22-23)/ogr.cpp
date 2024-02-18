#include <iostream>
using namespace std;

const int MAX = 1000;
long long pref[MAX + 1][MAX + 1];

int oblicz(int goraX, int goraY, int dolX, int dolY) {
    return pref[dolX][dolY] - pref[dolX][goraY - 1] - pref[goraX - 1][dolY] + pref[goraX - 1][goraY - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, R;
    cin >> n >> R;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            pref[i][j] = a + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << oblicz(max(i - R, 1), max(j - R, 1), min(i + R, n), min(j + R, n)) << " ";
        }
        cout << "\n";
    }

    return 0;
}
