#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
set<int> graf[MAX + 1];
vector<int> wynik;

void dfs(int v) {
	while (graf[v].size()) {
		int u = *graf[v].begin();
		graf[v].erase(u);
		graf[u].erase(v);
		dfs(u);
		wynik.push_back(v);
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
		graf[a].insert(b);
		graf[b].insert(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if (graf[i].size() & 1) {
			cout << "NIE";
			return 0;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (graf[i].size()) {
			dfs(i);
			break;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (graf[i].size()) {
			cout << "NIE";
			return 0;
		}
	}
	
	cout << "TAK\n";
	while (wynik.size()) {
		cout << wynik.back() << " ";
		wynik.pop_back();
	}

	return 0;
}

