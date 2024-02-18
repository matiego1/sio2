#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long maks = 0, dzien = 1, akt = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        akt += a;
        // cout << akt << endl;
        if (akt >= maks) {
            maks = akt;
            dzien = i;
        }
    }

    cout << dzien;
    return 0;
}