#include <iostream>
#include <vector>
using namespace std;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 182;
int tab[MAX + 2][MAX + 2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            tab[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        for (int j = 1; j <= m; j++) {
            if (s[j - 1] == '1') {
                tab[i][j] = 0;
            }
        }
    }

	// w lewo
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            tab[i][j] = min(tab[i][j], tab[i][j - 1] + 1);
        }
    }
    
    // w prawo
    for (int i = 1; i <= n; i++) {
        for (int j = m - 1; j >= 1; j--) {
            tab[i][j] = min(tab[i][j], tab[i][j + 1] + 1);
        }
    }
    
    // w dol
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            tab[j][i] = min(tab[j][i], tab[j - 1][i] + 1);
        }
    }
    
    // w gore
    for (int i = 1; i <= m; i++) {
        for (int j = n - 1; j >= 1; j--) {
            tab[j][i] = min(tab[j][i], tab[j + 1][i] + 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << tab[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}