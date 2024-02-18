#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int T[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> T[i];
    }

    int wynik = 0;
    for (int i = 1; i <= n; i++) {
        if (T[i] == -1) {
            continue;
        }
        wynik++;
        int x = i;
        while (T[x] != -1) {
            int pom = x;
            x = T[x];
            T[pom] = -1;
        }
    }
    cout << wynik;

    return 0;
}
