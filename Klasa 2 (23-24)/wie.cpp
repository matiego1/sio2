#include <iostream>
#include <algorithm>
#include <ctime>
#include "wie.h"
using namespace std;
typedef long long ll;

const long long MAX_BIN = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX = 300 * 1000;
int kolej[MAX + 1];

long long znajdz(int wieza, long long pocz) {
	long long kon = MAX_BIN;
	
	while (pocz < kon) {
		long long srodek = (pocz + kon) / 2;
		if (zamowienie(wieza, srodek)) {
			pocz = srodek + 1;
		} else {
			kon = srodek;
		}
	}
	
	return pocz - 1;
}

int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);

	srand(time(0));
	
    int n = wezN();
    
    for (int i = 1; i <= n; i++) {
        kolej[i] = i;
    }

	random_shuffle(kolej + 1, kolej + n + 1);

    long long wynik = 0, maks_wieza;
    for (int i = 1; i <= n; i++) {
    	if (!zamowienie(kolej[i], wynik + 1)) continue;
    	
    	long long akt = znajdz(kolej[i], wynik + 1);
        if (akt >= wynik) {
        	wynik = akt;
            maks_wieza = kolej[i];
        }
    }
    
    if (zamowienie(maks_wieza, MAX_BIN)) {
        odpowiedz(MAX_BIN);
        return 0;
    }
    
    odpowiedz(wynik);
    
    return 0;
}

