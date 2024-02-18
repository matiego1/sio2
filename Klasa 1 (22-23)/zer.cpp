#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int wynik = 0;

    while (n--) {
        long long a;
        cin >> a;
        if (a < 10) continue;
        a /= 10;
        if (a % 10 == 0) wynik++;
    }

    cout << wynik;

    return 0;
}
