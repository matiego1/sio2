#include <bits/stdc++.h>
using namespace std;

const int MAX = 200 * 1000;
const int INF = 1000 * 1000 * 1000;

string wej[MAX];
int wiersze[MAX];
int kolumny[MAX];

void generuj_wynik(int n, int l) {
    for (int i = l; i >= 1; i--) {
        for (int j = 2; j <= n; j++) {
            if (wej[j - 1][i] == wej[j][i]) {
                if (wiersze[j] == 0 || wiersze[j] >= INF) wiersze[j] = INF;
                else wiersze[j]++;
            } else if (wej[j - 1][i] > wej[j][i]) {
                wiersze[j] = INF;
            } else {
                wiersze[j] = 1;
            }
            kolumny[i] = max(kolumny[i], wiersze[j]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, l;
    cin >> n >> l;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        s = "$" + s;
        wej[i] = s;
    }

    generuj_wynik(n, l);

    int mini = l, pocz = 1;
    for (int i = 1; i <= l; i++) {
        if (kolumny[i] < mini) {
            mini = kolumny[i];
            pocz = i;
        }
    }

    cout << pocz << " " << pocz + mini - 1;

    return 0;
}