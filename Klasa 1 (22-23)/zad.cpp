#include <iostream>
using namespace std;

const int MAX = 200 * 1000;
int q[MAX];
int rozmiar = 0;

void dodaj(int x) {
    q[rozmiar] = x;
    rozmiar++;
}

int usun() {
    rozmiar--;
    return q[rozmiar];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    while (n--) {
        string typ;
        cin >> typ;
        if (typ == "+") {
            int x;
            cin >> x;
            dodaj(x);
        } else {
            cout << usun() << "\n";
        }
    }

    return 0;
}
