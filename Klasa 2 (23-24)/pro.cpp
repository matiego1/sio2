#include <iostream>
#include <map>
#include "cprolib.h"
using namespace std;

const int MAX = 300 * 1000;
map<int, int> ludzie[MAX + 1]; //czas, w ktorym miescie sa
int miasta[MAX + 1];

int rozwiaz(int v, int t) {
    auto p = ludzie[v].upper_bound(t);
    p--;
    return p->second;
}

int main() {

    int n, m, z;
    inicjuj(&n, &m, &z);

    for (int i = 1; i <= n; i++) {
        miasta[i] = i;
        ludzie[i][0] = i;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        pobierz_promocje(i, &u, &v);

        int czlowiekA = miasta[u];
        int czlowiekB = miasta[v];

        swap(miasta[u], miasta[v]);

        ludzie[czlowiekA][i] = v;
        ludzie[czlowiekB][i] = u;
    }

    //wypisz(n);

    for (int i = 0; i < z; i++) {
        int v, t;
        pobierz_zapytanie(&v, &t);
        odpowiedz(rozwiaz(v, t));
    }

    return 0;
}