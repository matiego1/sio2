#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
 
const int MAX = 200 * 1000;
const int K = 450;
 
struct Zapyt {
	int pocz, kon, indeks;
	
	para wart() {
		return {pocz / K, ((pocz / K) & 1) ? -kon : kon};
	}
};
 
int wej[MAX + 1];
Zapyt zapyt[MAX + 1];
int odp[MAX + 1];
int wynik = 0;
int zlicz[MAX + 1];
unordered_map<int, int> mapa;
int indeks = 0;

bool operator<(Zapyt& z1, Zapyt& z2) {
	return z1.wart() < z2.wart();
}
 
void dodaj(int wart) {
	zlicz[wart]++;
	if (zlicz[wart] == 1) {
		wynik++;
	}
}
 
void usun(int wart) {
	zlicz[wart]--;
	if (zlicz[wart] == 0) {
		wynik--;
	}
}
 
int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

void dodaj_wej(int i, int wart) {
	if (mapa.find(wart) == mapa.end()) {
		mapa[wart] = indeks++;
	}
	wej[i] = mapa[wart];
}
 
int main() {
	int n = wczytaj(' '), q = wczytaj('\n');
	
	for (int i = 1; i < n; i++) {
		dodaj_wej(i, wczytaj(' '));
	}
	dodaj_wej(n, wczytaj('\n'));
	
	for (int i = 1; i <= q; i++) {
		zapyt[i].pocz = wczytaj(' ');
		zapyt[i].kon = wczytaj('\n');
		zapyt[i].indeks = i;
	}
	
	sort(zapyt + 1, zapyt + 1 + q);
	
	int lewy = 1, prawy = 0;
	for (int i = 1; i <= q; i++) {
		while (lewy > zapyt[i].pocz) {
			lewy--;
			dodaj(wej[lewy]);
        }
        while (prawy < zapyt[i].kon) {
			prawy++;
			dodaj(wej[prawy]);
        }
        while (lewy < zapyt[i].pocz) {
			usun(wej[lewy]);
            lewy++;
        }
        while (prawy > zapyt[i].kon) {
            usun(wej[prawy]);
            prawy--;
        }
        odp[zapyt[i].indeks] = wynik;
	}
	
	for (int i = 1; i <= q; i++) {
		printf("%d\n", odp[i]);
	}
 
	return 0;
}
