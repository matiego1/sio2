#include <iostream>
using namespace std;

const double DELTA = 0.000001;
const int MAX = 6;
int a[MAX];

double W(double x) {
    return x*x*x*x*x*a[0] + x*x*x*x*a[1] + x*x*x*a[2] + x*x*a[3] + x*a[4] + a[5];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout.precision(6);
    cout << fixed;

    for (int i = 0; i < MAX; i++) {
        cin >> a[i];
    }

    double pocz = -5, kon = 0;
    while ((W(pocz) > 0) == (W(kon) > 0)) {
        pocz += 0.1;
    }

    if (W(pocz) > W(kon)) {
        swap(pocz, kon);
    }

    //W(pocz) < 0
    //W(kon) >= 0

    while (abs(kon - pocz) > DELTA) {
        double srodek = (pocz + kon) / 2.0;
        double wart = W(srodek);
        if (abs(wart) <= DELTA) {
            cout << srodek;
            return 0;
        }
        if (wart < 0) {
            pocz = srodek;
        } else {
            kon = srodek;
        }
    }

    if (abs(W(pocz)) < abs(W(kon))) {
        cout << pocz;
    } else {
        cout << kon;
    }

    return 0;
}