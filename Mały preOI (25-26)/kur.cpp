#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, int> para;

struct Kraw {
	int u;
	ll kanal, ulica;
};

const int MAX = 200 * 1000;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
vector<Kraw> graf[MAX + 1];
ll odleg[2][MAX + 1];
set<para> q;
int n;

void dijkstra(int start, int indeks) {
	for (int i = 1; i <= n; i++) odleg[indeks][i] = INF;
	
	odleg[indeks][start] = 0;
	q.insert({0, start});
	
	while (q.size()) {
		auto it = q.begin();
		int akt = it->second;
		q.erase(it);
		
		for (Kraw& k : graf[akt]) {
			int u = k.u;
			ll w = k.kanal;
			
			if (odleg[indeks][u] > odleg[indeks][akt] + w) {
				q.erase({odleg[indeks][u], u});
				odleg[indeks][u] = odleg[indeks][akt] + w;
				q.insert({odleg[indeks][u], u});
			}
		}
	}
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	n = wczytaj();
	int m = wczytaj();
	
	int rozmiar = 0;
	
	for (int i = 1; i <= m; i++) {
		int a = wczytaj(), b = wczytaj(), c = wczytaj(), d = wczytaj();
		rozmiar++;
		graf[a].push_back({b, c, d});
		graf[b].push_back({a, c, d});
	}
	
	int start = wczytaj(), meta = wczytaj();
	
	dijkstra(start, 0);
	dijkstra(meta, 1);
	
	ll mini = odleg[0][meta];
	for (int v = 1; v <= n; v++) {
		ll w1 = odleg[0][v];
		if (w1 == INF) continue;
		
		for (Kraw& k : graf[v]) {
			ll w2 = odleg[1][k.u];
			if (w2 == INF) continue;
			
			mini = min(mini, w1 + w2 + k.ulica);
		}
	}
	
	if (mini == INF) {
		putchar('-');putchar('1');
	} else {
		printf("%lld", mini);
	}

	return 0;
}
