#include <iostream>
using namespace std;

const int MAX = 1000;
int tab[MAX + 1][MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int a;
            cin >> a;
            tab[i][j] = tab[i - 1][j] + tab[i][j - 1] - tab[i - 1][j - 1] + a;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << tab[c][d] - tab[a - 1][d] - tab[c][b - 1] + tab[a - 1][b - 1] << "\n";
    }

    return 0;
}
