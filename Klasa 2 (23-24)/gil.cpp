#include <iostream>
#include <vector>
using namespace std;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
bool odwiedz[MAX + 1];
bool gildia[MAX + 1]; //true - krawcowie, false - szwaczki

void dfs(int v) {
	odwiedz[v] = true;
	for (int u : graf[v]) {
		if (!odwiedz[u]) {
			gildia[u] = !gildia[v];
			dfs(u);
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
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if (graf[i].empty()) {
			cout << "NIE";
			return 0;
		}
		dfs(i);
	}
	
	cout << "TAK\n";
	
	for (int i = 1; i <= n; i++) {
		if (gildia[i]) {
			cout << "K\n";
		} else {
			cout << "S\n";
		}
	}

	return 0;
}

