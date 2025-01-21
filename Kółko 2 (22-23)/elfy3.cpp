#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int INF = INT_MAX;
vector<int> graf[MAX + 1];
vector<int> graf2[2 * MAX + 1];
vector<int> stos;
bool odwie[2 * MAX + 1];
int order[MAX + 1];
int low[MAX + 1];
int wynik[2 * MAX + 1];
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

void dfs2(int v) {
	odwie[v] = true;
	
	for (int u : graf2[v]) {
		if (odwie[u]) continue;
		wynik[u] = wynik[v] + (u > MAX);
		dfs2(u);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, start;
	cin >> n >> m >> start;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	dfs(start, 0);
	
	for (int i = 1; i <= n; i++) odwie[i] = false;
	
	dfs2(start);
	
	for (int i = 1; i <= n; i++) cout << wynik[i] - (i != start) << " ";

	return 0;
}

