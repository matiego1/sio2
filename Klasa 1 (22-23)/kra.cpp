#include <iostream>
#define ll long long
using namespace std;

const int MAX = 300 * 1000;
ll wej[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    cin >> wej[0];
    for (int i = 1; i < n; i++) {
        ll a;
        cin >> a;
        wej[i] = min(wej[i - 1], a);
    }

    int dol = n;
    for (int i = 0; i < m; i++) {
        ll a;
        cin >> a;
        dol--;
        while (dol > 0 && wej[dol] < a) {
            dol--;
        }
        if (wej[dol] < a) {
            cout << 0;
            return 0;
        }
    }
    cout << dol + 1;

    return 0;
}
