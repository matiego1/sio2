#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int R = (1 << 18);
const int POCZ = R;
const int KON = 2 * R - 1;
vector<int> graf[MAX + 1];
para order[MAX + 1];
int dp[MAX + 1];
int tree[2 * R];
int tree2[2 * R];
int t = 0, wynik = 0;
int n;

void push(int v) {
	if (tree2[v] == 0) return;
	tree[2 * v] += tree2[v];
	tree2[2 * v] += tree2[v];
	tree[2 * v + 1] += tree2[v];
	tree2[2 * v + 1] += tree2[v];
	tree2[v] = 0;
}

int query(int pocz, int kon, int l = POCZ, int r = KON, int v = 1) {
	if (r < pocz || kon < l) return 0;
	if (pocz <= l && r <= kon) return tree[v];
	push(v);
	int srodek = (l + r) / 2; 
	return max(query(pocz, kon, l, srodek, 2 * v), query(pocz, kon, srodek + 1, r, 2 * v + 1));
}

void dodaj(int pocz, int kon, int wart, int l = POCZ, int r = KON, int v = 1) {
	if (r < pocz || kon < l) return;
	if (pocz <= l && r <= kon) {
		tree[v] += wart;
		tree2[v] += wart;
		return;
	}
	push(v);
	int srodek = (l + r) / 2;
	dodaj(pocz, kon, wart, l, srodek, 2 * v);
	dodaj(pocz, kon, wart, srodek + 1, r, 2 * v + 1);
	tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void dfs1(int v, int p) {
	order[v].first = ++t;
	
	if (p == 0) {
		dp[order[v].first] = (int) graf[v].size();
	} else {
		dp[order[v].first] = dp[order[p].first] + (int) graf[v].size() - 2;
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs1(u, v);
	}
	
	order[v].second = t;
}

void dfs2(int v, int p) {
	int dol = 0, gora = 0;
	if (p != 0) {
		gora = (int) graf[v].size() - 2;
		dol = (int) graf[v].size() - query(R + order[v].first, R + order[v].first);
		
		if (gora) dodaj(R + 1, R + t, gora);
		if (dol - gora) dodaj(R + order[v].first, R + order[v].second, dol - gora);
	}
	
	if (order[v].first > 1) {
		wynik = max(wynik, query(R + 1, R + order[v].first - 1));
	}
	if (order[v].first < t) {
		wynik = max(wynik, query(R + order[v].first + 1, R + t));
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs2(u, v);
	}
	
	if (p != 0) {
		if (gora) dodaj(R + 1, R + t, -gora);
		if (dol - gora) dodaj(R + order[v].first, R + order[v].second, -(dol - gora));
	}
}

int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	n = wczytaj('\n');
	
	for (int i = 1; i < n; i++) {
		int a = wczytaj(' '), b = wczytaj('\n');
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs1(1, 0);
	
	for (int i = 1; i <= t; i++) {
		tree[R + i] = dp[i];
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = max(tree[2 * i], tree[2 * i + 1]);
	}
	
	dfs2(1, 0);
	
	printf("%d", wynik);

	return 0;
}
