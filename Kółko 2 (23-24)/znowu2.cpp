#include <iostream>
using namespace std;
typedef long long ll;

const int MOD = 123456789;

void pomnoz(ll m1[2][2], ll m2[2][2]) {
    ll a = ((m1[0][0] * m2[0][0]) % MOD + (m1[0][1] * m2[1][0]) % MOD) % MOD;
    ll b = ((m1[1][0] * m2[0][0]) % MOD + (m1[1][1] * m2[1][0]) % MOD) % MOD;
    ll c = ((m1[0][0] * m2[0][1]) % MOD + (m1[0][1] * m2[1][1]) % MOD) % MOD;
    ll d = ((m1[1][0] * m2[0][1]) % MOD + (m1[1][1] * m2[1][1]) % MOD) % MOD;
    m1[0][0] = a;
    m1[0][1] = b;
    m1[1][0] = c;
    m1[1][1] = d;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    ll macierz[2][2] = {{0, 1}, {1, 1}};
    ll wynik[2][2] = {{0, 1}, {1, 1}};

    n--;

    while (n > 0) {
        if (n % 2 == 1) {
            pomnoz(wynik, macierz);
        }
        pomnoz(macierz, macierz);
        n /= 2;
    }

    cout << wynik[0][1];

    return 0;
}