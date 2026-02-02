#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 2000 * 1000;
int M = MAX;
vector<int> graf[MAX];
vector<int> graf2[MAX];
vector<int> graf_wej[MAX];
bool odwie[MAX];
int order[MAX];
int sklad[MAX];
int wynik[MAX];
para wej[MAX];
int t = 0;

void dodaj(int a, int b) {
	graf[a ^ 1].push_back(b);
	graf[b ^ 1].push_back(a);
	graf2[b].push_back(a ^ 1);
	graf2[a].push_back(b ^ 1);
}

void dodaj_xor(int a, int b) {
	dodaj(2 * a, 2 * b);
	dodaj(2 * a ^ 1, 2 * b ^ 1);
}

void dodaj_impl(int a, int b) {
	dodaj(2 * a ^ 1, 2 * b);
}

void dfs(int v) {
	odwie[v] = true;
	for (int u : graf[v]) {
		if (odwie[u]) continue;
		dfs(u);
	}
	order[++t] = v;
}

void sss(int v) {
	odwie[v] = true;
	sklad[v] = t;
	for (int u : graf2[v]) {
		if (odwie[u]) continue;
		sss(u);
	}
}

void policz_sss() {
	t = 0;
	for (int i = 1; i < M; i++) odwie[i] = false;
	for (int i = 1; i < M; i++) {
		if (odwie[i]) continue;
		dfs(i);
	}
	
	t = 0;
	for (int i = 1; i < M; i++) odwie[i] = false;
	for (int i = M - 1; i >= 1; i--) {
		if (odwie[order[i]]) continue;
		t++;
		sss(order[i]);
	}
}

void dfs_policz(int v, int p) {
	for (int u : graf_wej[v]) {
		if (u == p) continue;
		dodaj_impl(u, v);
		dfs_policz(u, v);
	}
}

bool policz(int n, int v) {
	for (int i = 1; i < M; i++) {
		graf[i].clear();
		graf2[i].clear();
	}
	
	for (int i = 1; i <= n; i++) {
		dodaj_xor(wej[i].first, wej[i].second);
	}
	
	dfs_policz(v, -1);
	
	policz_sss();
	
	for (int i = 1; i <= 2 * n; i++) {
		if (sklad[2 * i] == sklad[2 * i ^ 1]) return false;
		wynik[i] = (sklad[2 * i] > sklad[2 * i ^ 1]);
	}
	
	putchar('T');putchar('A');putchar('K');putchar('\n');
	for (int i = 1; i <= 2 * n; i++) {
		printf("%d ", wynik[i] ? 1 : 0);
	}
	putchar('\n');
	return true;
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

void rozwiaz() {
	int n = wczytaj();
	M = max(100, 6 * n);
	
	for (int i = 1; i < M; i++) {
		graf_wej[i].clear();
	}
	
	for (int i = 1; i < 2 * n; i++) {
		int a = wczytaj(), b = wczytaj();
		graf_wej[a].push_back(b);
		graf_wej[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		int a = wczytaj(), b = wczytaj();
		wej[i] = {a, b};
	}
	
	if (policz(n, wej[1].first)) return;
	if (policz(n, wej[1].second)) return;
	putchar('N');putchar('I');putchar('E');putchar('\n');
}

int main() {
	int z = wczytaj();
	
	while (z--) {
		rozwiaz();
	}

	return 0;
}

