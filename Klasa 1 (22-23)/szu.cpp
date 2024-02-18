#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int T[n];
    for (int i = 0; i < n; i++) {
        cin >> T[i];
    }

    int wynik = 0;
    int pop = T[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (T[i] >= pop) {
            wynik++;
            T[i] = pop - 1;
            if (pop == 1) {
                cout << -1;
                return 0;
            }
        }
        pop = T[i];
    }

    cout << wynik;
    return 0;
}
