#include <iostream>
#include <algorithm>
using namespace std;

struct Cukierek {
	int x, indeks;
};
struct Przedzial {
	int maks, pref, suff, rozmiar;
};

const int R = (1 << 21);
const int INF = 1000 * 1000 * 1000;
const int MAX = 1000 * 1000;
Cukierek wej[MAX + 1];
int tab[MAX + 1];
Przedzial tree[2 * R];
int wystapienia[R];

Przedzial polacz(Przedzial& lewy, Przedzial& prawy) {
	int maks = max(max(lewy.maks, prawy.maks), lewy.suff + prawy.pref);
	
	int pref = lewy.pref;
	if (lewy.pref == lewy.rozmiar) {
		pref += prawy.pref;
	}
	
	int suff = prawy.suff;
	if (prawy.suff == prawy.rozmiar) {
		suff += lewy.suff;
	}
	
	return {maks, pref, suff, lewy.rozmiar + prawy.rozmiar};
}

void update(int wart, bool dodaj) {
	int zmiana = 0;
	if (dodaj) {
		wystapienia[wart]++;
		if (wystapienia[wart] == 1) {
			zmiana = 1;
		}
	} else {
		wystapienia[wart]--;
		if (wystapienia[wart] == 0) {
			zmiana = -1;
		}
	}
	if (zmiana == 0) return;
	
	wart += R;
	
	if (zmiana == 1) {
		tree[wart] = {1, 1, 1, 1};
	} else {
		tree[wart] = {0, 0, 0, 1};
	}
	
	while (wart > 1) {
		wart /= 2;
		tree[wart] = polacz(tree[2 * wart], tree[2 * wart + 1]);
	}
}

int query() {
	return tree[1].maks;
}

bool czy_skrocic(int k, int pocz) {
	update(tab[pocz], false);
	if (query() >= k) {
		return true;
	}
	update(tab[pocz], true);
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	scanf("%d %d", &n, &k);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &wej[i].x);
		wej[i].indeks = i;
	}
	
	for (int i = R; i < 2 * R; i++) {
		tree[i].rozmiar = 1;
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i].rozmiar = tree[2 * i].rozmiar + tree[2 * i + 1].rozmiar;
	}
	
	sort(wej + 1, wej + n + 1, [](Cukierek& a, Cukierek& b) { return a.x < b.x; });
	
	int numer = 1;
	tab[wej[1].indeks] = numer;
	for (int i = 2; i <= n; i++) {
		if (wej[i].x == wej[i - 1].x + 1) {
			numer++;
		} else if (wej[i].x > wej[i - 1].x + 1) {
			numer += 2;
		}
		tab[wej[i].indeks] = numer;
	}
	
	int wynik = INF, wynik_pocz = -1;
	int pocz = 1;
	for (int kon = 1; kon <= n; kon++) {
		update(tab[kon], true);
		
		while (pocz < kon && czy_skrocic(k, pocz)) {
			pocz++;
		}
		
		if (query() >= k && kon - pocz + 1 < wynik) {
			wynik = kon - pocz + 1;
			wynik_pocz = pocz;
		}
	}
	
	if (wynik == INF) {
		printf("-1");
	} else {
		printf("%d\n%d %d", wynik, wynik_pocz, wynik_pocz + wynik - 1);
	}
	return 0;
}
