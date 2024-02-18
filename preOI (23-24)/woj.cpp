#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> para;

struct Zapyt {
	int typ, a, b;
};

const int MAX = 3 * 100 * 1000;
const int LOG = 19;
Zapyt zapyt[MAX + 1];
int kra[MAX + 1];
vector<para> graf[MAX + 1];
para order[MAX + 1];
int t = 1;
int prz[MAX + 1][LOG + 1];
int odleg[MAX + 1];

void dfs(int v, int ojciec) {
	order[v].first = (t++);
	
	prz[v][0] = ojciec;
	for (int i = 1; i <= LOG; i++) {
		prz[v][i] = prz[prz[v][i - 1]][i - 1];
	}
	
	for (para u : graf[v]) {
		if (u.first != ojciec) {
			odleg[u.first] = odleg[v] + u.second;
			dfs(u.first, v);
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
		if (!czy_poddrzewo(prz[b][i], a)) {
			b = prz[b][i];
		}
	}
	
	return prz[b][0];
}

int findd(int a) {
	if (a == kra[a]) return a;
	kra[a] = findd(kra[a]);
	return kra[a];
}
void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[a] = b;
}

int odleglosc(int a, int b) {
	return odleg[a] + odleg[b] - 2 * odleg[lca(a, b)];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
	}
	
	for (int i = 1; i <= m; i++) {
		int typ, a, b;
		cin >> typ >> a >> b;
		zapyt[i] = {typ, a, b};
		
		if (typ <= 2 && findd(a) != findd(b)) {
			int waga = (typ == 1 ? 0 : 1);
			graf[a].push_back({b, waga});
			graf[b].push_back({a, waga});
			unionn(a, b);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (order[i].first == 0) {
			dfs(i, i);
		}
	}	
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
	}
	
	for (int i = 1; i <= m; i++) {
		int typ = zapyt[i].typ, a = zapyt[i].a, b = zapyt[i].b;
		
		// Nowe polaczenie
		if (typ <= 2) {
			if (findd(a) == findd(b)) {
				int odl = odleglosc(a, b);
				if (typ == 1) {
					if (odl % 2 != 0) {
						cout << -1 << "\n";
					}
				} else {
					if (odl % 2 != 1) {
						cout << -1 << "\n";
					}
				}
			} else {
				unionn(a, b);
			}
		} else { // Zapytanie
			if (findd(a) != findd(b)) {
				cout << 0 << "\n";
				continue;
			}
			
			int odl = odleglosc(a, b);
			if (typ == 3) {
				cout << (odl % 2 == 0 ? 1 : 0) << "\n";
			} else {
				cout << (odl % 2 != 0 ? 1 : 0) << "\n";
			}
		}
	}
	
	return 0;
}
