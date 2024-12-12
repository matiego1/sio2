#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> para;
struct Zapyt {
	int typ, v;
};

const int INF = 1000 * 1000 * 1000;
const int MAX = 100 * 1000;
const int LOG = 17;
const int K = 320;
vector<int> graf[MAX + 1];
int odleg[MAX + 1];
int glebokosc[MAX + 1];
vector<int> czerwone;
int skok[MAX + 1][LOG + 1];
para order[MAX + 1];
int t = 0;
Zapyt zapytania[MAX + 1];

void dfs(int v, int ojciec) {
	glebokosc[v] = glebokosc[ojciec] + 1;
	order[v].first = (t++);
	
	skok[v][0] = ojciec;
	for (int i = 1; i <= LOG; i++) {
		skok[v][i] = skok[skok[v][i - 1]][i - 1];
	}
	
	for (int u : graf[v]) {
		if (u != ojciec) {
			dfs(u, v);
		}
	}
	
	order[v].second = t - 1;
}

bool czy_poddrzewo(int a, int b) {
	return (order[a].first <= order[b].first) && (order[b].first <= order[a].second);
}

int lca(int a, int b) {
	if (czy_poddrzewo(a, b)) return a;
	if (czy_poddrzewo(b, a)) return b;
	
	for (int i = LOG; i >= 0; i--) {
		if (!czy_poddrzewo(skok[b][i], a)) {
			b = skok[b][i];
		}
	}
	
	return skok[b][0];
}

int policz_odleg(int a, int b) {
	return glebokosc[a] + glebokosc[b] - (2 * glebokosc[lca(a, b)]);	
}

void bfs() {
	queue<int> q;
	for (int v : czerwone) {
		q.push(v);
		odleg[v] = 0;
	}
	czerwone.clear();
	
	while (!q.empty()) {
		int akt = q.front();
		q.pop();
		
		for (int v : graf[akt]) {
			if (odleg[v] <= odleg[akt] + 1) continue;
			odleg[v] = odleg[akt] + 1;
			q.push(v);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	odleg[1] = 0;
	for (int i = 1; i <= n; i++) {
		odleg[i] = INF;
	}
	
	dfs(1, 1);
	
	czerwone.push_back(1);
	while (m--) {
		int typ, v;
		cin >> typ >> v;
		
		if (typ == 1) {
			czerwone.push_back(v);
		} else {
			int wynik = odleg[v];
			for (int u : czerwone) {
				wynik = min(wynik, policz_odleg(v, u));
			}
			cout << wynik << "\n";
		}
		
		if (czerwone.size() >= K) {
			bfs();
		}
	}

	return 0;
}
 
