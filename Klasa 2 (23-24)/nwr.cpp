#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> para;

const int MAX = 2000;

int wej1[MAX + 1];
int wej2[MAX + 1];
int dp[MAX + 1][MAX + 1];
para zrodlo[MAX + 1][MAX + 1];
vector<int> wynik;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> wej1[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> wej2[i];
    }

    for (int i = 1; i <= n; i++) {
        int akt = 0;
        para akt_zrodlo = {0, 0};
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            zrodlo[i][j] = zrodlo[i - 1][j];
            if (wej1[i] == wej2[j] && akt + 1 > dp[i][j]) {
                 dp[i][j] = akt + 1;
                 zrodlo[i][j] = akt_zrodlo;
            }
            if (wej1[i] > wej2[j] && dp[i][j] > akt) {
                akt = dp[i][j];
                akt_zrodlo = {i, j};
            }
        }
    }

    int dlugosc = 0, poz = 0;
    para akt = {0, 0};
    for (int i = 1; i <= m; i++) {
        if (dp[n][i] > dlugosc) {
            dlugosc = dp[n][i];
            akt = zrodlo[n][i];
            poz = i;
        }
    }
    cout << dlugosc << "\n";
    wynik.push_back(wej2[poz]);
    while (akt.second != 0) {
        wynik.push_back(wej2[akt.second]);
        akt = zrodlo[akt.first][akt.second];
    }

    for (int i = wynik.size() - 1; i >= 0; i--) {
        cout << wynik[i] << " ";
    }

    return 0;
}
