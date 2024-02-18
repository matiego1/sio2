#include <iostream>
#include <bitset>
using namespace std;

const int MAX = 1000;
const int poz_x[4] = {1, 0, -1, 0};
const int poz_y[4] = {0, 1, 0, -1};
char wej[MAX + 2][MAX + 2];
int numer_grupy[MAX + 1][MAX + 1];
int numer_sowy[MAX + 1][MAX + 1];
bool wynik[MAX + 1][MAX + 1];

bitset<5700> pole[2 * MAX + 1];
int ilosc[2 * MAX + 1];
int n, m;

int pozycja(int x, int y) {
	return (y + n) * (2 * m + 1) + (x + m);
}

void generuj_grupy(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int xn = x + poz_x[i], yn = y + poz_y[i];
		if (wej[xn][yn] != 'S') continue;
		
		if (numer_grupy[xn][yn] != 0) continue;
		numer_grupy[xn][yn] = numer_grupy[x][y];
		
		generuj_grupy(xn, yn);
	}
}

void generuj_pole(int grupa, int x, int y, int deltaX, int deltaY) {
	for (int i = 0; i < 4; i++) {
		int xn = x + poz_x[i], yn = y + poz_y[i];
		if (wej[xn][yn] != 'S') continue;
		
		int dXn = deltaX + poz_x[i], dYn = deltaY + poz_y[i];
		
		int poz = pozycja(dXn, dYn);
		if (pole[grupa].test(poz)) continue;
		pole[grupa].set(poz, 1);
		ilosc[grupa]++;
		
		generuj_pole(grupa, xn, yn, dXn, dYn);
	}
}

int wczytaj_int(char koniec) {
	int x = 0, znak;
	while ((znak = getchar()) != koniec) {
		x = x * 10 + (znak - '0');
	}
	return x;
}

bool sprawdz(int x, int y) {
	for (int y1 = 1; y1 <= n; y1++) {
		for (int x1 = 1; x1 <= m; x1++) {
			if (wej[x1][y1] != 'S') continue;
			if (numer_grupy[x][y] == numer_grupy[x1][y1]) continue;
			if ((int) (pole[numer_sowy[x][y]] | pole[numer_sowy[x1][y1]]).count() != ilosc[numer_sowy[x1][y1]]) continue;
			return false;
		}
	}
	return true;
}

int main() {
	n = wczytaj_int(' ');
	m = wczytaj_int('\n');
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			wej[x][y] = (char) getchar();
		}
		getchar();
	}
	
	int grupa = 0;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			if (numer_grupy[x][y] != 0) continue;
			
			numer_grupy[x][y] = ++grupa;
			generuj_grupy(x, y);
		}
	}
	
	int sowa = 0;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			if (wej[x][y] != 'S') continue;
			
			numer_sowy[x][y] = ++sowa;
			
			pole[sowa].set(pozycja(0, 0), 1);
			ilosc[sowa]++;
			generuj_pole(sowa, x, y, 0, 0);
		}
	}
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			
		}
	}
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			if (wej[x][y] != 'S') {
				putchar(wej[x][y]);
				continue;
			}
			
			putchar(sprawdz(x, y) ? 'S' : 'x');
		}
		putchar('\n');
	}

	return 0;
}

