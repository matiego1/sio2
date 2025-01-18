#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> para;

const ld EPS = 0.000000001;
const int MAX = 100 * 1000;
para wej[MAX + 1];
para pred[MAX + 1];
para poz[MAX + 1];
int n;

ld bok(ld t) {
	for (int i = 1; i <= n; i++) {
		poz[i].first = wej[i].first + t * pred[i].first;
		poz[i].second = wej[i].second + t * pred[i].second;
	}
	
	int lewy = 1, prawy = 1, dolny = 1, gorny = 1;
	for (int i = 2; i <= n; i++) {
		if (poz[i].first < poz[lewy].first) lewy = i;
		if (poz[i].first > poz[prawy].first) prawy = i;
		if (poz[i].second < poz[dolny].second) dolny = i;
		if (poz[i].second > poz[gorny].second) gorny = i;
	}
	
	return max(abs(poz[lewy].first - poz[prawy].first), abs(poz[dolny].second - poz[gorny].second));
}

int wczytaj(char koniec) {
	int znak = getchar(), x = 0, ujemne = 1;
	if (znak == '-') {
		ujemne = -1;
	} else {
		x = znak - '0';
	}
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x * ujemne;
}

int main() {
	n = wczytaj('\n');
	
	for (int i = 1; i <= n; i++) {
		wej[i].first = wczytaj(' ');
		wej[i].second = wczytaj(' ');
		pred[i].first = wczytaj(' ');
		pred[i].second = wczytaj('\n');
	}
	
	ld pocz = 0, kon = INT_MAX;
	while (abs(pocz - kon) >= EPS) {
		ld s1 = pocz + (kon - pocz) / 3;
		ld s2 = kon - (kon - pocz) / 3;
		
		ld w1 = bok(s1);
		ld w2 = bok(s2);
		
		if (w1 < w2) {
			kon = s2;
		} else {
			pocz = s1;
		}
	}
	
	printf("%Lf", bok(pocz));

	return 0;
}

