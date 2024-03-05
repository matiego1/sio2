#include <iostream>
#include <map>
using namespace std;

const int MAX = 200 * 1000;
map<string, int> mapa;
int kra[MAX + 1];

int findd(int x) {
    if (kra[x] == x) return x;
    kra[x] = findd(kra[x]);
    return kra[x];
}

void unionn(int a, int b) {
    a = findd(a);
    b = findd(b);
    if (a == b) return;
    kra[a] = b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 1; i <= MAX; i++) {
        kra[i] = i;
    }

    int indeks = 0;

    int q;
    cin >> q;
    while (q--) {
        string s, a, b;
        cin >> s >> a >> b;

        int nrA = mapa[a], nrB = mapa[b];
        if (a != b && nrA == 0) {
            indeks++;
            mapa[a] = indeks;
            nrA = indeks;
        }
        if (a != b && nrB == 0) {
            indeks++;
            mapa[b] = indeks;
            nrB = indeks;
        }

        if (s[0] == 'c') {
            if (a != b) unionn(nrA, nrB);
        } else {
            if (a == b) {
                cout << "Tak\n";
            } else {
                cout << (findd(nrA) == findd(nrB) ? "Tak" : "Nie") << "\n";
            }
        }
    }

    return 0;
}
