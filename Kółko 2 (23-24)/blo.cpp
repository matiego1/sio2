#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
vector<int> graf2[2 * MAX + 1];
int odwie[MAX + 1];
vector<int> stos;
int low[MAX + 1];
int order[2 * MAX + 1];
int maxorder[2 * MAX + 1];
int dp[2 * MAX + 1];
int t = 0, rozmiar = MAX;

void dfs(int v, int p) {
	odwie[v] = true;
	low[v] = order[v] = ++t;
	stos.push_back(v);
	
	for (int u : graf[v]) {
		if (u == p) continue;
		if (odwie[u]) {
			low[v] = min(low[v], order[u]);
		} else {
			dfs(u, v);
			low[v] = min(low[v], low[u]);
			
			if (low[u] >= order[v]) {
				rozmiar++;
				
				graf2[rozmiar].push_back(v);
				graf2[v].push_back(rozmiar);
				
				int ostatnie = v;
				while (ostatnie != u) {
					graf2[rozmiar].push_back(stos.back());
					graf2[stos.back()].push_back(rozmiar);
					
					ostatnie = stos.back();
					stos.pop_back();
				}
			}
		}
	}
}

void dfs2(int v, int p) {
	order[v] = ++t;
	dp[v] = (v <= MAX);
	
	for (int u : graf2[v]) {
		if (u == p) continue;
		dfs2(u, v);
		dp[v] += dp[u];
	}
	
	maxorder[v] = t;
}

bool czy_poddrzewo(int a, int b) {
	return (order[a] <= order[b] && order[b] <= maxorder[a]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	dfs(1, 0);
	
	t = 0;
	dfs2(1, 0);
	
	for (int v = 1; v <= n; v++) {
		ll wynik = 0;
		if (graf2[v].size() > 1) {
			ll suma = 0;
			for (int u : graf2[v]) {
				if (czy_poddrzewo(v, u)) {
					suma += dp[u];
				} else {
					suma += n - dp[v];
				}
			}
			
			for (int u : graf2[v]) {
				ll akt = 0;
				if (czy_poddrzewo(v, u)) {
					akt = dp[u];
				} else {
					akt = n - dp[v];
				}
				wynik += akt * (suma - akt);
			}
		}
		
		cout << wynik + 2 * (n - 1) << "\n";
	}

	return 0;
}