#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 5000;
vector<int> graf[MAX + 1];
bool odwie[MAX + 1];
int order[MAX + 1];
int low[MAX + 1];
int zlicz[MAX + 1];
vector<para> mosty;
int t = 0;

void dfs(int v, int p) {
	odwie[v] = true;
	order[v] = ++t;
	low[v] = t;
	bool byl_ojciec = false;
	for (int u : graf[v]) {
		if (u == p && !byl_ojciec) {
			byl_ojciec = true;
			continue;
		}
		if (odwie[u]) {
			low[v] = min(low[v], order[u]);
		} else {
			dfs(u, v);
			low[v] = min(low[v], low[u]);
			if (low[u] > order[v]) {
				mosty.push_back({v, u});
				zlicz[u]++;
				zlicz[v]++;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		if (a == b) continue;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs(1, 0);
	
	int wynik = 0;
	for (para most : mosty) {
		if (zlicz[most.first] == 1) wynik++;
		if (zlicz[most.second] == 1) wynik++;
	}
	cout << (wynik + 1) / 2;

	return 0;
}

