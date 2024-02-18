#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int tab[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    long long suma = 0;
    for (int i = 0; i < k; i++) {
        cin >> tab[i];
        suma += tab[i];
    }
    long long wynik = suma;

    for (int i = k; i < n; i++) {
        cin >> tab[i];
        suma += tab[i];
        suma -= tab[i - k];
        wynik = min(wynik, suma);
    }

    cout << wynik;

    return 0;
}