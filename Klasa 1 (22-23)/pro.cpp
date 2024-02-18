#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int maks = 2 * n + 2;
    int a = 1, b = n;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if ((2 * (i + n / i)) > maks) {
                maks = 2 * (i + n / i);
                a = i;
                b = n / i;
            }
        }
    }
    cout << a << " " << b;

    return 0;
}
