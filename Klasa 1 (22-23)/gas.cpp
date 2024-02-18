#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int wej[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> wej[i];
    }

    int wynik = n + 5;

    int kon = 0;
    int suma = 0;
    for (int pocz = 0; pocz < n; pocz++) {
        suma += wej[pocz];
        while (kon < pocz && suma - wej[kon] >= k) {
            suma -= wej[kon];
            kon++;
        }
        if (suma >= k) {
            wynik = min(wynik, pocz - kon + 1 - suma);
        }
    }

    if (wynik == n + 5) {
        cout << "NIE";
    } else {
        cout << wynik;
    }
    return 0;
}