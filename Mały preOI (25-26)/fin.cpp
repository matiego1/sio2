#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Zapyt {
	char typ;
	int a, b;
};

const int MAX = 200 * 1000;
const int LOG = 18;
vector<int> graf[MAX + 1];
int prz[MAX + 1][LOG + 1];
int kra[MAX + 1];
para order[MAX + 1];
int odleg[MAX + 1];
int dlug[MAX + 1];
para wierz[MAX + 1];
Zapyt zapyt[MAX + 1];

int t = 0;

void dfs_lca(int v, int p) {
	order[v].first = ++t;
	
	prz[v][0] = p;
	for (int k = 1; k <= LOG; k++) {
		prz[v][k] = prz[prz[v][k - 1]][k - 1];
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		odleg[u] = odleg[v] + 1;
		dfs_lca(u, v);
	}
	
	order[v].second = t;
}

bool czy_poddrzewo(int a, int b) {
	return (order[a].first <= order[b].first) && (order[b].first <= order[a].second);
}

int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	
	for (int k = LOG; k >= 0; k--) {
		if (!czy_poddrzewo(prz[b][k], a)) {
			b = prz[b][k];
		}
	}
	
	return prz[b][0];
}

int odleglosc(int a, int b) {
	return odleg[a] + odleg[b] - 2 * odleg[lca(a, b)];
}

int findd(int x) {
	if (kra[x] == x) return x;
	kra[x] = findd(kra[x]);
	return kra[x];
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
 	
	if (a == b) return;
	
	int u1[2] = {wierz[a].first, wierz[a].second};
	int u2[2] = {wierz[b].first, wierz[b].second};
	
	int maks = dlug[a], w1 = u1[0], w2 = u1[1];
	
	if (dlug[b] > maks) {
		maks = dlug[b];
		w1 = u2[0];
		w2 = u2[1];
	}
	
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			int o = odleglosc(u1[i], u2[j]);
			if (o > maks) {
				maks = o;
				w1 = u1[i];
				w2 = u2[j];
			}
		}
	}
	
	kra[b] = a;
	dlug[a] = maks;
	wierz[a] = {w1, w2};
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), q = wczytaj();
	
	for (int i = 1; i <= q; i++) {
		zapyt[i].typ = getchar();
		getchar(); // spacja
		
		if (zapyt[i].typ == 'S') {
			int a = wczytaj(), b = wczytaj();
			
			zapyt[i].a = a;
			zapyt[i].b = b;
			
			graf[a].push_back(b);
			graf[b].push_back(a);
		} else {
			zapyt[i].a = wczytaj();
		}
	}
	
	dfs_lca(1, 1);
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
		wierz[i] = {i, i};
		dlug[i] = 0;
	}
	
	for (int i = 1; i <= q; i++) {
		if (zapyt[i].typ == 'S') {
			unionn(zapyt[i].a, zapyt[i].b);
		} else {
			int v = zapyt[i].a;
			para u = wierz[findd(v)];
			
			printf("%d\n", max(odleglosc(v, u.first), odleglosc(v, u.second)));
		}
	}

	return 0;
}

