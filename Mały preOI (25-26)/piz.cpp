#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int R = (1 << 18);
int wej[MAX + 1];
int tree[2 * R];
para tab[MAX + 1];

void dodaj(int v, int wart) {
	v += R;
	tree[v] += wart;
	
	while (v > 1) {
		v /= 2;
		tree[v] = max(tree[2 * v], tree[2 * v + 1]);
	}
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), k = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		tab[i].first = wczytaj();
		tab[i].second = i;
	}
	
	sort(tab + 1, tab + 1 + n);
	int wart = 0, pop = -1;
	for (int i = 1; i <= n; i++) {
		if (tab[i].first != pop) {
			pop = tab[i].first;
			wart++;
		}
		wej[tab[i].second] = wart;
	}
	
	int wynik = 0;
	
	int lewy = 1, rozne = 0;
	for (int prawy = 1; prawy <= n; prawy++) {
		dodaj(wej[prawy], 1);
		if (tree[wej[prawy] + R] == 1) rozne++;
		
		while (lewy < prawy && rozne > k + 1) {
			dodaj(wej[lewy], -1);
			if (tree[wej[lewy] + R] == 0) rozne--;
			lewy++;
		}
		
		wynik = max(wynik, tree[1]);
	}
	
	printf("%d", wynik);

	return 0;
}

