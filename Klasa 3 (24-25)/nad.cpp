#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 3000 * 1000;
int poczatki[MAX + 1];
int konce[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int a, s;
        cin >> a >> s;
        poczatki[a] = s;
        konce[a + s] += 1;
    }

    ll maks = -1, maksi = -1;
    ll mini = 2 * 1000 * 1000 * 1000, minii = -1;

    ll ile = 0, sila = 0;
    for (int i = 1; i <= m; i++) {
        sila -= ile;
        ile -= konce[i];
        if (poczatki[i] > 0) {
            ile++;
            sila += poczatki[i];
        }

        if (sila > maks) {
            maks = sila;
            maksi = i;
        }
        if (sila < mini) {
            mini = sila;
            minii = i;
        }
    }

    cout << maksi << " " << minii;

    return 0;
}
