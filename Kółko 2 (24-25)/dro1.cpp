#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

const int MAX = 50 * 1000;


vector<int> graf[MAX + 1];
vector<int> graf2[MAX + 1];
set<int> graf3[MAX + 1];
int order[MAX + 1];
bool odwie[MAX + 1];

int sklad[MAX + 1];
int rozmiar[MAX + 1];
int poziom[MAX + 1];
int DP[MAX + 1];

int t = 0;

void dfs(int v) {
	odwie[v] = true;
	for (int u : graf[v]) {
		if (!odwie[u]) {
			dfs(u);
		}
	}
	order[++t] = v;
}

void sss(int v) {
	odwie[v] = true;
	sklad[v] = t;
	rozmiar[t]++;
	for (int u : graf2[v]) {
		if (!odwie[u]) {
			sss(u);
		}
	}
}

void dfs_poziom(int v) {
	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf2[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if (!odwie[i]) {
			dfs(i);
		}
	}
	
	t = 0;
	for (int i = 1; i <= n; i++) {
		odwie[i] = false;
	}
	for (int i = n; i >= 1; i--) {
		if (!odwie[order[i]]) {
			t++;
			sss(order[i]);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int u : graf[i]) {
			if (sklad[i] != sklad[u]) {
				graf3[sklad[i]].insert(sklad[u]);
			}	
		}
	}
	for (int i = 1; i <= t; i++) {
		for (int u : graf3[i]) {
			poziom[u]++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= t; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	vector<int> topo;
	while (!q.empty()) {
		int akt = q.front();
		q.pop();
		topo.push_back(akt);
		for (int u : graf3[akt]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
	}
	
	for (int i = topo.size() - 1; i >= 0; i--) {
		DP[topo[i]] = rozmiar[topo[i]];
		for (int u : graf3[topo[i]]) {
			DP[topo[i]] += DP[u];
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << DP[sklad[i]] - 1 << "\n";
	}
	
	return 0;
}