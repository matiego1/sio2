#include <iostream>
#include <vector>
using namespace std;

const int LOG = 19;
const int MAX = 500 * 1000;
const int MINI = -2000 * 1000 * 1000;

struct Info {
	vector<pair<int, int>> kra;
	int order;
	int maxOrder;
	pair<int, int> prz[LOG + 1]; //wierzcho³ek do którego skaczemy, maksymalna wartoœæ na tej œcie¿ce
};

Info graf[MAX + 1];
int t = 0;

void dfs(int v, int p, int odleg) {
	graf[v].order = ++t;
	
	graf[v].prz[0] = make_pair(p, odleg);
	for (int k = 1; k <= LOG; k++) {
		graf[v].prz[k] = make_pair(graf[graf[v].prz[k - 1].first].prz[k - 1].first, max(graf[v].prz[k - 1].second, graf[graf[v].prz[k - 1].first].prz[k - 1].second));
	}
	
	for (pair<int, int> u : graf[v].kra) {
		if (u.first != p) {
			dfs(u.first, v, u.second);
		}
	}
	
	graf[v].maxOrder = t;
}

bool czy_poddrzewo(int a, int b) {
	return (graf[a].order <= graf[b].order) && (graf[b].order <= graf[a].maxOrder);
}

int lca(int a, int b) {
	if (a == b) return 0;
	
	int wynik = MINI;
	if (!czy_poddrzewo(b, a)) {
		for (int k = LOG; k >= 0; k--) {
			if (!czy_poddrzewo(graf[b].prz[k].first, a)) {
				wynik = max(wynik, graf[b].prz[k].second);
				b = graf[b].prz[k].first;
			}
		}
		wynik = max(wynik, graf[b].prz[0].second);
		b = graf[b].prz[0].first;
	}
	if (a == b) return wynik;
	
	for (int k = LOG; k >= 0; k--) {
		if (!czy_poddrzewo(graf[a].prz[k].first, b)) {
			wynik = max(wynik, graf[a].prz[k].second);
			a = graf[a].prz[k].first;
		}
	}	
	wynik = max(wynik, graf[a].prz[0].second);
	return wynik;
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
	
	dfs(1, 1, 0);
	
	int a, b;
	cin >> a;
	while (a != -1) {
		cin >> b;
		
		cout << lca(a, b) << "\n";
		
		cin >> a;
	}
	
	return 0;
}
