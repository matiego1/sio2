#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int MOD = 1000 * 1000 * 1000 + 7;
vector<int> graf[MAX + 1];
vector<int> graf2[MAX + 1];
bool odwie[MAX + 1];
int order[MAX + 1];
int sklad[MAX + 1];
int mini[MAX + 1];
int rozmiar[MAX + 1];
int wej[MAX + 1];
int t = 0;

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

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		wej[i] = wczytaj();
	}
	
	int m = wczytaj();
	
	for (int i = 1; i <= m; i++) {
		int a = wczytaj(), b = wczytaj();
		graf[a].push_back(b);
		graf2[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if (odwie[i]) continue;
		dfs(i);
	}
	
	t = 0;
	for (int i = 1; i <= n; i++) odwie[i] = false;
	for (int i = n; i >= 1; i--) {
		if (odwie[order[i]]) continue;
		t++;
		sss(order[i]);
	}
	
	for (int i = 1; i <= t; i++) mini[i] = INT_MAX;
	for (int i = 1; i <= n; i++) {
		mini[sklad[i]] = min(mini[sklad[i]], wej[i]);
	}
	
	for (int i = 1; i <= n; i++) {
		if (wej[i] == mini[sklad[i]]) {
			rozmiar[sklad[i]]++;
		}
	}
	
	ll wynik = 0, sposoby = 1;
	for (int i = 1; i <= t; i++) {
		wynik += mini[i];
		sposoby = (sposoby * rozmiar[i]) % MOD;
	}
	
	printf("%lld %lld", wynik, sposoby);

	return 0;
}
