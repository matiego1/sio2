#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 1000 * 1000;
ll wej[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;
    for (int i = 1; i <= n; i++) cin >> wej[i];

    if (n == 1) {
        cout << wej[1] * (t / 2 + 1);
        return 0;
    }

    ll wynik = 0, suma = 0;
    for (int i = 1; i < n; i++) {
        int pozostaly = t - i + 1;
        if (pozostaly < 0) break;
        
        suma += wej[i];
        
        ll akt = suma;
        akt += (wej[i] + wej[i + 1]) * (pozostaly / 2);
        if (pozostaly % 2 == 1) akt += wej[i + 1];
        
        wynik = max(wynik, akt);
    }
    cout << wynik;

    return 0;
}
