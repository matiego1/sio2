#include <iostream>
#include <vector>
#define ull unsigned long long
using namespace std;

ull nwd(ull a, ull b) {
    if (b > a) swap(a, b);
    if (b > 0) {
        return nwd(b, a % b);
    }
    return a;
}

void rozwiaz(ull a, ull b) {
    ull x = nwd(a, b);
    b /= nwd(a, b / x) * x;
    a /= x;
    cout << a << " " << b << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    while (n--) {
        ull a, b;
        cin >> a >> b;
        rozwiaz(a, b);
    }

    return 0;
}
