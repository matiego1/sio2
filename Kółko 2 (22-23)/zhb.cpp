#include <iostream>
#include <vector>
using namespace std;

const int LOG = 20;
const int POT_LOG = (1 << LOG);
const int MAX = 1000 * 1000;

struct Info {
	vector<int> kra;
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
	
	for (int u : graf[v].kra) {
		if (u != p) {
			graf[u].h = graf[v].h + 1;
			dfs(u, v);
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

int skocz(int v, int ile) {
	for (int k = POT_LOG, potega = LOG; k >= 1; k /= 2, potega--) {
		if (ile >= k) {
			ile -= k;
			v = graf[v].prz[potega];
		}
	}
	return v;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, akt, q;
	cin >> n >> akt >> q;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].kra.push_back(b);
		graf[b].kra.push_back(a);
	}
	
	graf[1].h = 0;
	dfs(1, 1);
	
	while (q--) {
		int cel, czas;
		cin >> cel >> czas;
		
		int LCA = lca(akt, cel);
		int X = graf[akt].h + graf[cel].h - 2 * graf[LCA].h;
		
		if (X <= czas) {
			akt = cel;
		} else {
			int doLca = graf[akt].h - graf[LCA].h;
			
			if (czas < doLca) {
				akt = skocz(akt, czas);
			} else if (czas == doLca) {
				akt = LCA;
			} else {
				akt = skocz(cel, X - czas);
			}
		}
		
		cout << akt << " ";
		
	}

	return 0;
}
