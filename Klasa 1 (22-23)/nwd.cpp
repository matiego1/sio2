#include <iostream>
using namespace std;

int nwd(int a, int b) {
    if (b > 0) {
        return nwd(b, a % b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int a;
    cin >> a;

    int wynik = a;
    n--;

    while (n--) {
        cin >> a;
        wynik = nwd(wynik, a);
    }

    cout << wynik;
    return 0;
}
