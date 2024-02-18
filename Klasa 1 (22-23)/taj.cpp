#include <iostream>
#include "tajtabbibl.h"
using namespace std;

const int INF = 1000 * 1000 * 1000;



int rozwiaz(int indeks) {
    int lewy = -INF - 4, prawy = INF + 4;
    while (lewy < prawy) {
        int srodek = (lewy + prawy - 1) / 2;
        if (wieksze(indeks, srodek)) {
            lewy = srodek + 1;
        } else {
            prawy = srodek;
        }
    }
    return lewy;
}

int main() {
    int n = inicjuj();

    int mini = INF + 10, miniI = -1;
    int maks = -INF - 10, maksI = -1;
    for (int i = 0; i < n; i++) {
        int a = rozwiaz(i);
        if (a < mini) {
            mini = a;
            miniI = i;
        }
        if (a > maks) {
            maks = a;
            maksI = i;
        }
    }

    odpowiedz(miniI, maksI);

    return 0;
}
