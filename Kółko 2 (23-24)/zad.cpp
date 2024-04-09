#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 200 * 1000;

struct Wierzcholek {
    int ojciec, wartosc;
};

Wierzcholek graf[MAX + 1];
int operacje[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int akt_wierz = 0;
    int ilosc = 0;
    graf[akt_wierz].ojciec = -1;

    for (int i = 1; i <= n; i++) {
        char typ;
        cin >> typ;

        operacje[i] = akt_wierz;

        if (typ == '-') {
            akt_wierz = graf[akt_wierz].ojciec;
        } else if (typ == '+') {
            ilosc++;
            graf[ilosc].ojciec = akt_wierz;
            cin >> graf[ilosc].wartosc;
            akt_wierz = ilosc;
        } else {
            int a;
            cin >> a;
            akt_wierz = operacje[i - a];
        }

        if (graf[akt_wierz].ojciec == -1) {
            cout << -1 << "\n";
        } else {
            cout << graf[akt_wierz].wartosc << "\n";
        }
    }

    return 0;
}
