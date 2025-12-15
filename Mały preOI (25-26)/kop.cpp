#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
typedef pair<ll, int> parall;

struct Kraw {
	int a, b, c;
};

const int MAX = 100 * 1000;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int LOG = 17;
vector<para> graf[MAX + 1];
set<pair<para, int>> krawedzie;
int prz[MAX + 1][LOG + 1];
para order[MAX + 1];
ll odleg[MAX + 1];
bool odwie[MAX + 1];
int t = 0;
para zapyt[MAX + 1];
ll odpowiedzi[MAX + 1];
priority_queue<parall, vector<parall>, greater<parall>> q;

void dfs(int v, int p) {
	odwie[v] = true;
	for (para& u : graf[v]) {
		if (u.first == p) continue;
		if (odwie[u.first]) {
			if (v < u.first) {
				krawedzie.insert({{v, u.first}, u.second});
			} else {
				krawedzie.insert({{u.first, v}, u.second});
			}
			u.second = -1;
			continue;
		}
		dfs(u.first, v);
	}
}

void dfs_lca(int v, int p) {
	order[v].first = ++t;
	
	prz[v][0] = p;
	for (int k = 1; k <= LOG; k++) {
		prz[v][k] = prz[prz[v][k - 1]][k - 1];
	}
	
	for (para u : graf[v]) {
		if (u.second == -1) continue;
		if (u.first == p) continue;
		odleg[u.first] = odleg[v] + u.second;
		dfs_lca(u.first, v);
	}
	
	order[v].second = t;
}

bool czy_poddrzewo(int a, int b) {
	return (order[a].first <= order[b].first) && (order[b].first <= order[a].second);
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

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

void dijkstra(int n, int Q, int v) {
	for (int i = 1; i <= n; i++) odleg[i] = INF;
		
	odleg[v] = 0;
	q.push({0, v});
	
	while (q.size()) {
		int akt = q.top().second;
		q.pop();
		
		for (para p : graf[akt]) {
			if (p.second == -1) continue;
			if (odleg[p.first] > odleg[akt] + p.second) {
				odleg[p.first] = odleg[akt] + p.second;
				q.push({odleg[p.first], p.first});
			}
		}
	}
	
	for (int i = 1; i <= Q; i++) {
		odpowiedzi[i] = min(odpowiedzi[i], odleg[zapyt[i].first] + odleg[zapyt[i].second]);
	}
}

int main() {
	int n = wczytaj(), m = wczytaj();
	
	for (int i = 1; i <= m; i++) {
		int a = wczytaj(), b = wczytaj(), c = wczytaj();
		
		graf[a].push_back({b, c});
		graf[b].push_back({a, c});
	}
	
	dfs(1, -1);
	dfs_lca(1, 1);
	
	int Q = wczytaj();
	
	for (int i = 1; i <= Q; i++) {
		int x = wczytaj(), y = wczytaj();
		zapyt[i] = {x, y};
		odpowiedzi[i] = odleg[x] + odleg[y] - 2 * odleg[lca(x, y)];
	}
	
	for (pair<para, int> kraw : krawedzie) {
		int v = kraw.first.first;
		int u = kraw.first.second;
		int w = kraw.second;
		
		for (para& p : graf[v]) {
			if (p.first == u) p.second = w;
		}
		for (para& p : graf[u]) {
			if (p.first == v) p.second = w;
		}
		
//		cout << "Dokladam "<<v << " " << u << "Wa " << w<< "\n";
		
		dijkstra(n, Q, v);
		dijkstra(n, Q, u);
	}
	
	for (int i = 1; i <= Q; i++) {
		printf("%lld\n", odpowiedzi[i]);
	}

	return 0;
}

