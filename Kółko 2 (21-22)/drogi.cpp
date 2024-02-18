#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 10000;

vector<int> graf[MAX + 1];
vector<int> graf2[MAX + 1];
int sklad[MAX + 1];
int order[MAX + 1];
bool odwie[MAX + 1];
int t = 0;

void dfs(int v) {
	odwie[v] = true;
	for (int u : graf[v]) {
		if (!odwie[u]) {
			dfs(u);
		}
	}
	order[t++] = v;
}

void sss(int v) {
	odwie[v] = true;
	sklad[v] = t;
	for (int u : graf2[v]) {
		if (!odwie[u]) {
			sss(u);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		if (a == b) continue;
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
	for (int i = n - 1; i >= 0; i--) {
		if (!odwie[order[i]]) {
			sss(order[i]);
			t++;
		}
	}
	
	for (int i = 0; i < t; i++) {
		graf2[i].clear();
	}
	for (int i = 1; i <= n; i++) {
		for (int u : graf[i]) {
			if (sklad[i] != sklad[u]) {
				graf2[sklad[i]].push_back(sklad[u]);
			}	
		}
	}
	
	int poczatki = 0, konce = 0;
	for (int i = 0; i < t; i++) {
		if (graf2[i].size() == 0) konce++;
	}
	for (int i = 0; i < t; i++) {
		odwie[i] = true;
	}
	for (int i = 0; i < t; i++) {
		for (int u : graf2[i]) {
			odwie[u] = false;
		}
	}
	for (int i = 0; i < t; i++) {
		if (odwie[i]) poczatki++;
	}
	
	if (poczatki == 1 && konce == 1) {
		cout << 0;
	} else {
		cout << max(poczatki, konce);
	}
		
	return 0;
}