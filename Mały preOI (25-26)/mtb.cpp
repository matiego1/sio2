#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Kraw {
	int waga, a, b;
};
bool operator<(Kraw& k1, Kraw& k2) {
	return k1.waga < k2.waga;
}

const int MAX = 200 * 1000;
const int LOG = 18;
int wej[MAX + 1];
Kraw krawedzie[MAX + 1];
int kra[MAX + 1];
vector<int> graf[MAX + 1];
para order[MAX + 1];
bool odwie[MAX + 1];
int t = 0;
int maksimum[MAX + 1][LOG + 1];
int prz[MAX + 1][LOG + 1];

int findd(int x) {
	if (x == kra[x]) return x;
	kra[x] = findd(kra[x]);
	return kra[x];
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	
	if (a == b) return;
	
	kra[b] = a;
}

void dfs_lca(int v, int p) {
	odwie[v] = true;
	
	order[v].first = ++t;
	
	prz[v][0] = p;
	maksimum[v][0] = max(wej[v], wej[p]);
	for (int k = 1; k <= LOG; k++) {
		prz[v][k] = prz[prz[v][k - 1]][k - 1];
		maksimum[v][k] = max(maksimum[v][k - 1], maksimum[prz[v][k - 1]][k - 1]);
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs_lca(u, v);
	}
	
	order[v].second = t;
}

bool czy_poddrzewo(int a, int b) {
	return (order[a].first <= order[b].first) && (order[b].first <= order[a].second);
}

int znajdz_lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	
	for (int k = LOG; k >= 0; k--) {
		if (!czy_poddrzewo(prz[b][k], a)) {
			b = prz[b][k];
		}
	}
	
	return prz[b][0];
}

int maks_sciezka(int a, int b) {
	int lca = znajdz_lca(a, b);
	
	int wynik = max(wej[lca], max(wej[a], wej[b]));
	
	for (int k = LOG; k >= 0; k--) {
		if (!czy_poddrzewo(prz[a][k], lca)) {
			wynik = max(wynik, maksimum[a][k]);
			a = prz[a][k];
		}
		if (!czy_poddrzewo(prz[b][k], lca)) {
			wynik = max(wynik, maksimum[b][k]);
			b = prz[b][k];
		}
	}
	
	return wynik;
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), m = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		wej[i] = wczytaj();
		kra[i] = i;
	}
	
	for (int i = 1; i <= m; i++) {
		int a = wczytaj(), b = wczytaj();
		krawedzie[i] = {max(wej[a], wej[b]), a, b};
	}
	
	sort(krawedzie + 1, krawedzie + 1 + m);
	
	for (int i = 1; i <= m; i++) {
		int a = krawedzie[i].a, b = krawedzie[i].b;
		if (findd(a) == findd(b)) continue;
		
		unionn(a, b);
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if (odwie[i]) continue;
		dfs_lca(i, i);
	}
	
	int q = wczytaj();
	
	while (q--) {
		int pocz = wczytaj(), kon = wczytaj(), energia = wczytaj();
		
		if (findd(pocz) != findd(kon)) {
			putchar('N');putchar('I');putchar('E');putchar('\n');
			continue;
		}
		
		int maks_wys = maks_sciezka(pocz, kon);
		int pocz_wys = wej[pocz];
		
		if (maks_wys <= pocz_wys + energia) {
			putchar('T');putchar('A');putchar('K');putchar('\n');
		} else {
			putchar('N');putchar('I');putchar('E');putchar('\n');
		}
	}

	return 0;
}

