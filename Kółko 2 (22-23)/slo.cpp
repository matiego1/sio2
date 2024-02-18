#include <iostream>
#include <vector>
using namespace std;

const int LOG = 19;
const int MAX = 500 * 1000;

struct Info {
	vector<pair<int, int>> kra;
	int order;
	int maxOrder;
	int prz[LOG + 1];
	long long h;	
};

Info graf[MAX + 1];
int t = 0;

void dfs(int v, int p) {
	graf[v].order = ++t;
	
	graf[v].prz[0] = p;
	for (int k = 1; k <= LOG; k++) {
		graf[v].prz[k] = graf[graf[v].prz[k - 1]].prz[k - 1];
	}
	
	for (pair<int, int> u : graf[v].kra) {
		if (u.first != p) {
			graf[u.first].h = graf[v].h + u.second;
			dfs(u.first, v);
		}
	}
	
	graf[v].maxOrder = t;
}

bool czy_poddrzewo(int a, int b) {
	return (graf[a].order <= graf[b].order) && (graf[b].order <= graf[a].maxOrder);
}

int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	
	for (int k = LOG; k >= 0; k--) {
		if (!czy_poddrzewo(graf[b].prz[k], a)) {
			b = graf[b].prz[k];
		}
	}
	
	return graf[b].prz[0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].kra.push_back(make_pair(b, c));
		graf[b].kra.push_back(make_pair(a, c));
	}
	
	graf[1].h = 0;
	dfs(1, 1);
	
	int a, b;
	cin >> a;
	while (a != -1) {
		cin >> b;
		
		cout << graf[a].h + graf[b].h - (2 * graf[lca(a, b)].h) << "\n";
		
		cin >> a;
	}
	
	return 0;
}
