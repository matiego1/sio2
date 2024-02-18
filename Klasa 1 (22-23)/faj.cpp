#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int wej[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> wej[i];
    }

    int kon = 0;
    int suma = 0;
    for (int pocz = 0; pocz < n; pocz++) {
        suma += wej[pocz];
        if (suma == 2137) {
            cout << "TAK";
            return 0;
        }
        while (kon < pocz && suma > 2137) {
            suma -= wej[kon];
            kon++;
        }
        if (suma == 2137) {
            cout << "TAK";
            return 0;
        }
    }
    cout << "NIE";

    return 0;
}
