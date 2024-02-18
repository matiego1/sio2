#include <iostream>
#include <vector>
using namespace std;

const int MAX = 500;
const int INF = 1000 * 1000 * 1000;
int odleg[MAX + 1][MAX + 1];

int wczytaj_int_znak(char koniec) {
	bool ujemne = false;
	int x = 0, znak = getchar();
	if (znak == '-') {
		ujemne = true;
	} else {
		x = znak - '0';
	}
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return ujemne ? -x : x;
}

int wczytaj_int(char koniec) {
	int x = 0, znak;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

void wypisz_int(int x) {
	if (x == 0) return;
	wypisz_int(x / 10);
	putchar((x % 10) + '0');
}

int main() {
	int n = wczytaj_int(' '), m = wczytaj_int('\n');
	
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			odleg[i][j] = INF;
			odleg[j][i] = INF;
		}
	}
	
	for (int i = 1; i <= m; i++) {
		int a = wczytaj_int(' '), b = wczytaj_int(' '), c = wczytaj_int_znak('\n');
		if (a != b) odleg[a][b] = c;
	}
	
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (odleg[i][k] < INF && odleg[k][j] < INF && odleg[i][j] > odleg[i][k] + odleg[k][j]) {
					odleg[i][j] = max(-INF, odleg[i][k] + odleg[k][j]);
				}
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (odleg[i][k] < INF && odleg[k][k] < 0 && odleg[k][j] < INF) {
					odleg[i][j] = -INF;
				}
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (odleg[i][j] == -INF) {
				putchar('-');
				putchar('o');
				putchar('o');
				putchar(' ');
			} else if (odleg[i][j] == INF) {
				putchar('*');
				putchar(' ');
			} else {
				if (odleg[i][j] == 0) {
					putchar('0');
				} else {
					if (odleg[i][j] < 0) {
						putchar('-');
						wypisz_int(-odleg[i][j]);
					} else {
						wypisz_int(odleg[i][j]);
					}
				}
				putchar(' ');
			}
		}
		putchar('\n');
	}

	return 0;
}
