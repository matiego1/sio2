#include <bits/stdc++.h>
using namespace std;

const int MAX = 200 * 1000;
int wej[MAX + 1];
int przod[MAX + 1];
int tyl[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
    }

    przod[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (wej[i] > wej[i - 1]) {
            przod[i] = przod[i - 1] + 1;
        } else {
            przod[i] = 1;
        }
    }

    tyl[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (wej[i] > wej[i + 1]) {
            tyl[i] = tyl[i + 1] + 1;
        } else {
            tyl[i] = 1;
        }
    }

    int wynik = 1;
    for (int i = 1; i <= n; i++) {
        wynik = max(wynik, przod[i] + tyl[i] - 1);
    }
    cout << wynik;

    return 0;
}
