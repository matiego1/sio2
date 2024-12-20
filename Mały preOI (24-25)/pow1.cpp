#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
const int LOG = 19;
vector<int> graf[MAX + 1];
int prz[MAX + 1][LOG + 1];
para order[MAX + 1];
int wierz[MAX + 1];
int odleg[MAX + 1];
bool wlaczony[MAX + 1];
set<int> wlaczone;
int t = 0;


void dfs(int v, int p) {
	order[v].first = ++t;
	wierz[t] = v;
	
	prz[v][0] = p;
	for (int i = 1; i <= LOG; i++) {
		prz[v][i] = prz[prz[v][i - 1]][i - 1];
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		odleg[u] = odleg[v] + 1;
		dfs(u, v);
	}
	
	order[v].second = t;
}

bool czy_poddrzewo(int a, int b) {
	return order[a].first <= order[b].first && order[b].first <= order[a].second;
}

int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	for (int i = LOG; i >= 0; i--) {
		if (!czy_poddrzewo(prz[b][i], a)) {
			b = prz[b][i];
		}
	}
	return prz[b][0];
}

int odleglosc(int a, int b) {
	return odleg[a] + odleg[b] - 2 * odleg[lca(a, b)];
}

void zmien(int v, int znak, int& wynik) {
	auto nast = wlaczone.upper_bound(order[v].first);
	auto pop = nast;
	pop--;
	
	int nast_v, pop_v;
	if (nast == wlaczone.end()) {
		nast_v = wierz[*wlaczone.begin()];
	} else {
		nast_v = wierz[*nast];
	}
	if (nast == wlaczone.begin()) {
		pop_v = wierz[*wlaczone.rbegin()];
	} else {
		pop_v = wierz[*pop];
	}
	
	wynik += znak * odleglosc(v, nast_v);
	wynik += znak * odleglosc(v, pop_v);
	wynik -= znak * odleglosc(pop_v, nast_v);
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs(1, 1);
	 
	int wynik = 0;
	while (q--) {
		int v;
		cin >> v;
		
		if (wlaczony[v]) {
			wlaczony[v] = false;
			wlaczone.erase(order[v].first);
			if (wlaczone.size() == 1) {
				wynik -= 2 * odleglosc(wierz[*wlaczone.begin()], v);
			} else if (wlaczone.size() > 1) {
				zmien(v, -1, wynik);
			}
		} else {
			wlaczony[v] = true;
			if (wlaczone.size() == 1) {
				wynik += 2 * odleglosc(wierz[*wlaczone.begin()], v);
			} else if (wlaczone.size() > 1) {
				zmien(v, 1, wynik);
			}
			wlaczone.insert(order[v].first);
		}
		
		cout << wynik / 2 << "\n";
	}

	return 0;
}

