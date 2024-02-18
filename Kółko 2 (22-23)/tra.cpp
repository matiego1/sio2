#include <iostream>
#include <vector>
using namespace std;

const int LOG = 17;
const int MAX = 100 * 1000;

vector<int> graf[MAX + 1];
pair<int, int> order[MAX + 1];
int prz[MAX + 1][LOG + 1];
int t = 0;

void dfs(int v, int p) {
	order[v].first = ++t;
	
	prz[v][0] = p;
	for (int k = 1; k <= LOG; k++) {
		prz[v][k] = prz[prz[v][k - 1]][k - 1];
	}
	
	for (int u : graf[v]) {
		if (u != p) {
			dfs(u, v);
		}
	}
	
	order[v].second = t;
}

//czy B jest w poddrzewie A
bool czy_poddrzewo(int a, int b) {
	return order[a].first <= order[b].first && order[b].first <= order[a].second;
}

int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	
	for (int k = LOG; k >= 0; k--) {
		if (!czy_poddrzewo(prz[b][k], a)) {
			b = prz[b][k];
		}
	}
	
	return prz[b][0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs(1, 1);
	
	int q;
	cin >> q;
	while (q--) {
		int a, b, c;
		cin >> a >> b >> c;
		int l = lca(a, b);
		int lA = lca(a, c);
		int lB = lca(b, c);
		if (l == c || (lA == l && lB == c) || (lB == l && lA == c)) {
			cout << "TAK\n";
		} else {
			cout << "NIE\n";
		}
 	}
	
	return 0;
}
