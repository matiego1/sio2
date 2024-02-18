#include <iostream>
using namespace std;
typedef long long ll;

const int MAX = 1000 * 1000;
ll phi[MAX + 1];

void policz_phi() {
    phi[1] = 1;
    for (int i = 2; i <= MAX; i++) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            for (int j = 2 * i; j <= MAX; j += i) {
                if (phi[j] == 0) {
                    phi[j] = j;
                }
                phi[j] = (phi[j] / i) * (i - 1);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    policz_phi();

    ll n, m;
    cin >> n >> m;

    ll wynik = 0;
    for (int i = 1; i <= min(n, m); i++) {
        wynik += (n / i) * (m / i) * phi[i];
    }
    cout << wynik;

    return 0;
}
