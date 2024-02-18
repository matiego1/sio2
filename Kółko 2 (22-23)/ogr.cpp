#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Punkt {
    ll x, y;
};

const int MAX = 500 * 1000;
Punkt wej[2][MAX + 1];
Punkt otoczka[2][MAX + 1];
int rozmiar[2];
Punkt pierwszy_pkt;

ll odleg_kw(Punkt& a, Punkt& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll iloczyn_bez_znaku(Punkt& a, Punkt& b, Punkt& c) {
	return (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);	
}

int iloczyn(Punkt& a, Punkt& b, Punkt& c) {
	ll wynik = iloczyn_bez_znaku(a, b, c);
	if (wynik == 0) return 0;
	return (wynik > 0 ? 1 : -1);
}

bool porownaj_katy(Punkt& a, Punkt& b) {
	int kierunek = iloczyn(pierwszy_pkt, b, a);
	if (kierunek == 0) {
		return odleg_kw(pierwszy_pkt, a) < odleg_kw(pierwszy_pkt, b);
	}
	return (kierunek == 1);
}


void wygeneruj_otoczke(int n, int gracz) {
    int min_pkt = 1;
    for (int i = 2; i <= n; i++) {
    	if (wej[gracz][i].x < wej[gracz][min_pkt].x) {
    		min_pkt = i;
		} else if (wej[gracz][i].x == wej[gracz][min_pkt].x && wej[gracz][i].y < wej[gracz][min_pkt].y) {
			min_pkt = i;
		}
    }
	
	swap(wej[gracz][1], wej[gracz][min_pkt]);
	
	pierwszy_pkt = wej[gracz][1];
	sort(wej[gracz] + 2, wej[gracz] + 1 + n, porownaj_katy);
	
	rozmiar[gracz] = 3;
	otoczka[gracz][1] = wej[gracz][1];
	otoczka[gracz][2] = wej[gracz][2];
	otoczka[gracz][3] = wej[gracz][3];
	
	for (int i = 4; i <= n; i++) {
		while (rozmiar[gracz] >= 2 && iloczyn(otoczka[gracz][rozmiar[gracz] - 1], otoczka[gracz][rozmiar[gracz]], wej[gracz][i]) != -1) {
			rozmiar[gracz]--;
		}
		otoczka[gracz][++rozmiar[gracz]] = wej[gracz][i];
	}
}

bool czy_wewnatrz(Punkt& punkt, int gracz) {
	Punkt p0 = otoczka[gracz][1];
	Punkt p1 = otoczka[gracz][2];
	Punkt pn = otoczka[gracz][rozmiar[gracz]];    
    
    int ilo1 = iloczyn(p1, p0, pn);
    
    ll ilo2 = iloczyn(p1, p0, punkt);
    if (ilo2 != 0 && ilo2 != ilo1) return false;
    
    ll ilo3 = iloczyn(pn, p0, punkt);
    if (ilo3 != 0 && ilo3 != -ilo1) return false;
    
    if (ilo2 == 0) return odleg_kw(p1, p0) >= odleg_kw(punkt, p0);

	int pocz = 2, kon = rozmiar[gracz];
	while (kon - pocz > 1) {
		int srodek = (pocz + kon) / 2;
		if (iloczyn(otoczka[gracz][srodek], p0, punkt) >= 0) {
			pocz = srodek;
		} else {
			kon = srodek;
		}
	}
	
    Punkt a = otoczka[gracz][pocz];
    Punkt b = otoczka[gracz][pocz + 1];
    Punkt c = p0;
	
	ll x1 = abs(iloczyn_bez_znaku(b, a, c));
	ll x2 = abs(iloczyn_bez_znaku(a, punkt, b)) + abs(iloczyn_bez_znaku(b, punkt, c)) + abs(iloczyn_bez_znaku(c, punkt, a));
    return x1 == x2;
}

int wczytaj_int(char koniec) {
	bool ujemne = false;
	int znak = getchar(), x = 0;
	if (znak == '-') {
		ujemne = true;
	} else {
		x = znak - '0';
	}
	while ((znak = getchar()) != koniec) {
		x = x * 10 + znak - '0';
	}
	return (ujemne ? -x : x);
}

int main() {
	int n = wczytaj_int('\n');
	
	if (n == 1) {
		putchar('0');
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		wej[0][i] = {wczytaj_int(' '), wczytaj_int('\n')};
	}
	
	if (n == 2) {
		printf("%Lf", 2 * sqrtl(odleg_kw(wej[0][1], wej[0][2])));
		return 0;
	}
	
	wygeneruj_otoczke(n, 0);
	
	ld wynik = 0;
	
	for (int i = 1; i < rozmiar[0]; i++) {
		wynik += sqrtl(odleg_kw(otoczka[0][i], otoczka[0][i + 1]));
	}
	wynik += sqrtl(odleg_kw(otoczka[0][rozmiar[0]], otoczka[0][1]));
	
	printf("%Lf", wynik);

	return 0;
}