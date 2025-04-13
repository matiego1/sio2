#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_C = 1000 * 1000;
int MAX = MAX_C;
int R;
vector<int> graf[MAX_C];
vector<int> graf2[MAX_C];
bool odwie[MAX_C];
int order[MAX_C];
int sklad[MAX_C];
para wej[MAX_C];
int t = 0;

void dodaj_or(int a, int b) {
	graf[a ^ 1].push_back(b);
	graf[b ^ 1].push_back(a);
	graf2[b].push_back(a ^ 1);
	graf2[a].push_back(b ^ 1);
}

void dodaj_impl(int a, int b) {
	dodaj_or(2 * a + 1, 2 * b);
}

void dodaj(int pocz, int kon, int x) {
	x = 2 * (x + R) + 1;
	if (pocz > kon) return;
	pocz = max(R, pocz + R) - 1;
	kon = min(2 * R - 1, kon + R) + 1;
	
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			dodaj_or(2 * (pocz + 1) + 1, x);
		}
		if (kon % 2 == 1) {
			dodaj_or(2 * (kon - 1) + 1, x);
		}
		pocz /= 2;
		kon /= 2;
	}
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
	for (int i = 1; i < MAX; i++) odwie[i] = false;
	for (int i = 1; i < MAX; i++) {
		if (odwie[i]) continue;
		dfs(i);
	}
	
	t = 0;
	for (int i = 1; i < MAX; i++) odwie[i] = false;
	for (int i = MAX - 1; i >= 1; i--) {
		if (odwie[order[i]]) continue;
		t++;
		sss(order[i]);
	}
}

bool sprawdz(int n, int m, int d) {
    for (int i = 1; i < MAX; i++) {
    	graf[i].clear();
    	graf2[i].clear();
	}
	for (int i = 1; i <= m; i++) {
		dodaj_or(2 * (R + wej[i].first), 2 * (R + wej[i].second));
	}
	
	for (int i = R - 1; i >= 1; i--) {
		dodaj_impl(2 * i, i);
		dodaj_impl(2 * i + 1, i);
	}
	
	for (int i = 1; i <= n; i++) {
		dodaj(i - d + 1, i - 1, i);
		dodaj(i + 1, i + d - 1, i);
	}
	
	policz_sss();
	
	for (int i = 1; i <= n; i++) {
		if (sklad[2 * (R + i)] == sklad[2 * (R + i) + 1]) return false;
	}
	
	return true;
}

int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

int rozwiaz() {
	int n = wczytaj(' '), m = wczytaj('\n');
	
	for (int i = 1; i <= m; i++) {
		wej[i].first = wczytaj(' ');
		wej[i].second = wczytaj('\n');
	}
	
    R = (1 << (32 - __builtin_clz(n)));
    MAX = 4 * R + 10;
	
	int pocz = 1, kon = n;
	while (pocz < kon) {
		int srodek = (pocz + kon + 1) / 2;
		if (sprawdz(n, m, srodek)) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
		}
	}
	
	return pocz;
}

int main() {
	int q = wczytaj('\n');
	
	while (q--) {
		printf("%d\n", rozwiaz());
	}

	return 0;
}

 
