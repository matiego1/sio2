#include <iostream>
#define ull unsigned long long
using namespace std;

ull nwd(ull a, ull b) {
    if (b > a) swap(a, b);
    if (b > 0) {
        return nwd(b, a % b);
    }
    return a;
}
ull nww(ull a, ull b) {
    return a * b / nwd(a, b);
}

void rozwiaz(ull l1, ull m1, ull l2, ull m2) {
    ull m = nww(m1, m2);
    ull l = m / m1 * l1 + m / m2 * l2;

    ull x = nwd(m, l);
    m /= x;
    l /= x;
    cout << l << " " << m << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        ull a, b, c, d;
        cin >> a >> b >> c >> d;
        rozwiaz(a, b, c, d);
    }
    return 0;
}
