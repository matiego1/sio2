#include <iostream>
using namespace std;

//0 = nozyce, 1 = kamien, 2 = papier
int ruch(string& s, int poz) {
    if (s[poz] == '8') return 0;
    if (s[poz] == '(') return 1;
    return 2;
}

//-1 = a, 0 = remis, 1 = b
int sprawdz(int a, int b) {
    if (a == b) return 0;
    if (a == 0) return b == 1 ? 1 : -1;
    if (a == 1) return b == 0 ? -1 : 1;
    if (a == 2) return b == 0 ? 1 : -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string a, b;
    cin >> a >> b;

    int wynikA = 0, wynikB = 0;

    for (int i = 0; i < a.length(); i += 2) {
        int x = sprawdz(ruch(a, i), ruch(b, i));
        if (x == -1) {
            wynikA += 1;
        } else if (x == 1) {
            wynikB += 1;
        }
    }

    if (wynikA > wynikB) cout << "WYGRANA";
    else if (wynikA == wynikB) cout << "REMIS";
    else cout << "PRZEGRANA";

    return 0;
}