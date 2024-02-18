#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    int reszty[k];
    for (int i = 0; i < k; i++) reszty[i] = false;

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        reszty[a % k] = true;
    }

    int wynik = 0;
    for (int i = 0; i < k; i++) wynik += reszty[i];
    cout << wynik;

    return 0;
}
