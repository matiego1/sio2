#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, int> para;

const int MAX = 1000 * 1000;
const int RED = 1;
const int BLACK = 0;
vector<int> graf[MAX + 1];
int wej[MAX + 1];
int parzyste = 0, nieparzyste = 0;

void dfs_zlicz(int v, int p, int gleb) {
	if (gleb % 2 == 0) parzyste++;
	else nieparzyste++;
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs_zlicz(u, v, gleb + 1);
	}
}

para dfs(int v, int p, int kolor) {
	ll wynik = 0, akt = 0;
	for (int u : graf[v]) {
		if (u == p) continue;
		para x = dfs(u, v, 1 ^ kolor);
		wynik += x.first;
		akt += x.second;
	}
	
	if (wej[v] != kolor) {
		akt += (kolor == RED ? 1 : -1);
	}
	wynik += abs(akt);
	
	return {wynik, akt};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	int ile_czer = 0, ile_czar = 0;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		wej[i] = (c == 'R' ? RED : BLACK);
		
		if (c == 'R') ile_czer++;
		else ile_czar++;
	}
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs_zlicz(1, 1, 0);
	
	ll wynik = LLONG_MAX;
	if (parzyste == ile_czer && nieparzyste == ile_czar) {
		wynik = min(wynik, dfs(1, 1, RED).first);
	}
	if (parzyste == ile_czar && nieparzyste == ile_czer) {
		wynik = min(wynik, dfs(1, 1, BLACK).first);
	}
	
	if (wynik == LLONG_MAX) cout << -1;
	else cout << wynik;

	return 0;
}

