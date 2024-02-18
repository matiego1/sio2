#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 30 * 1000;
int wej[MAX];

bool sprawdz(int a, int b, int c) {
    return a + b > c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> wej[i];
    }

    sort(wej, wej + n);

    int wynik = 0;
    int kon = 0;
    for (int pocz = 0; pocz < n; pocz++) {
        while (kon + 3 <= pocz && !sprawdz(wej[kon], wej[kon + 1], wej[pocz])) {
            kon++;
        }
        if (pocz - kon >= 2 && sprawdz(wej[kon], wej[kon + 1], wej[pocz])) {
            wynik = max(wynik, pocz - kon + 1);
        }
    }

    cout << wynik;

    return 0;
}
