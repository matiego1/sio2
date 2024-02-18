#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
para wej[MAX + 1];
int rozmiar = 0;
para tree[MAX + 1];

void dodaj(para wartosc) {
	rozmiar++;
	tree[rozmiar] = wartosc;
	int indeks = rozmiar;
	while (indeks > 1 && tree[indeks] > tree[indeks / 2]) {
		swap(tree[indeks], tree[indeks / 2]);
		indeks /= 2;
	}
}

void zbuduj(int indeks) {
	int maks = indeks;
	if (2 * indeks <= rozmiar && tree[2 * indeks] > tree[maks]) maks = 2 * indeks;
	if (2 * indeks + 1 <= rozmiar && tree[2 * indeks + 1] > tree[maks]) maks = 2 * indeks + 1;
	if (maks == indeks) return;
	swap(tree[indeks], tree[maks]);
	zbuduj(maks);
}

para usun_max() {
	para wynik = tree[1];
	tree[1] = tree[rozmiar];
	rozmiar--;
	zbuduj(1);
	return wynik;
}

int main() {
	int n, m;
	scanf("%d %d", &m, &n);
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		wej[i] = {b, a};
	}

	sort(wej + 1, wej + 1 + n);
	int indeks = 1;
	
	int wynik = 0;
	for (int i = 1; i <= m; i++) {
		while (indeks <= n && wej[indeks].first <= i) {
			dodaj({wej[indeks].second, wej[indeks].first});
			indeks++;
		}
		if (rozmiar == 0) continue;
		para akt = usun_max();
		wynik += akt.first;
	}
	
	printf("%d", wynik);
	
	return 0;
}