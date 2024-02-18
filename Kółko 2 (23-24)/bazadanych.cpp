#include <iostream>
#include <map>
using namespace std;

map<int, int> mapa;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    while (n--) {
        int konto, oper;
        cin >> konto >> oper;

        if (oper >= 0) {
            mapa[konto] += oper;
            cout << mapa[konto] << "\n";
        } else {
            if (mapa[konto] + oper < 0) {
                cout << "NIE\n";
            } else {
                mapa[konto] += oper;
                cout << mapa[konto] << "\n";
            }
        }
    }

    return 0;
}