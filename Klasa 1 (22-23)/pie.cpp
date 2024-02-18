#include <iostream>
using namespace std;

const int MAX = 1000 * 1000 * 1000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long  n;
    cin >> n;

    long long pocz = 1, kon = MAX + 1;
    while (pocz < kon) {
        long long srodek = (pocz + kon) / 2;
        if (srodek * srodek > n) {
            kon = srodek;
        } else {
            pocz = srodek + 1;
        }
    }
    cout << kon;

    return 0;
}
