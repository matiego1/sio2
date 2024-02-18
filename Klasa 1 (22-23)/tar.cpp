#include <iostream>
using namespace std;

const int MAX = 20 * 1000;
int wej[MAX];

int rozwiaz(int n, int k) {
    int wynik = 0;
    int kon = 0;
    int koszt = 0;
    for (int pocz = 0; pocz < n; pocz++) {
        while (kon < pocz && koszt > k) {
            koszt -= max(0, wej[kon + 1] - wej[kon]);
            kon++;
        }
        if (koszt <= k) {
            wynik = max(pocz - kon + 1, wynik);
        }
        koszt += max(0, wej[pocz + 1] - wej[pocz]);
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> wej[i];
    }

    int wynik = rozwiaz(n, k);

    for (int i = 0; i < n / 2; i++) {
        swap(wej[i], wej[n - i - 1]);
    }

    cout << max(wynik, rozwiaz(n, k));

    return 0;
}
