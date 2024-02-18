#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;

    int wynik = 1;
    while (n >= wynik) {
        n -= wynik;
        wynik *= 2;
    }

    if (n > 0) {
        wynik *= 2;
    }

    cout << wynik;

    return 0;
}
