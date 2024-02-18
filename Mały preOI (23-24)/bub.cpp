#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> para;

struct Zapytanie {
	int typ, a, b;
};
Zapytanie make_zapytanie(int typ, int a, int b) {
	return {typ, a, b};
}

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 1000 * 1000;
const int LOG = 20; // starczy ???
const int MAX_Q = 5 * 100 * 1000;

vector<int> graf[MAX];
int stolica[MAX];
int odleg[MAX];
int skoki[MAX][LOG + 1];
para order[MAX];
int t = 0;

Zapytanie zapytania[MAX_Q + 1];

// Find & Union
int kra[MAX];
int findd(int x) {
    if (kra[x] == x) return x;
    kra[x] = findd(kra[x]);
    return kra[x];
}

void unionn(int a, int b) {
    a = findd(a);
    b = findd(b);
    if (a == b) return;
    
    kra[a] = b;
}

// bfs do podzadania 1
void bfs(int pocz) {
	queue<int> q;
	q.push(pocz);
	odleg[pocz] = 0;
	
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		
		for (int u : graf[v]) {
			if (odleg[u] != INF) continue;
			odleg[u] = odleg[v] + 1; 
			q.push(u);
		}
	}
}

// Liczenie tablicy skoki i order
void dfs(int v, int ojciec) {
	order[v].first = (t++);

	odleg[v] = odleg[ojciec] + 1; 

	skoki[v][0] = ojciec;
	for (int i = 1; i <= LOG; i++) {
		skoki[v][i] = skoki[skoki[v][i - 1]][i - 1];
	}
	
	for (int u : graf[v]) {
		if (u != ojciec) {
			dfs(u, v);
		}
	}

	order[v].second = t - 1;
}

// Laczenie grafu
void polacz_bez_grafu(int s, int a, int b) {
	a = stolica[findd(a)];
	b = stolica[findd(b)];
	
	unionn(a, s);
	unionn(b, s);
	stolica[findd(a)] = s;
}
void polacz(int s, int a, int b) {
	a = stolica[findd(a)];
	b = stolica[findd(b)];
	
	unionn(a, s);
	unionn(b, s);
	stolica[findd(a)] = s;
	
	graf[a].push_back(s);
	graf[b].push_back(s);
	graf[s].push_back(a);
	graf[s].push_back(b);
}

// Czy w poddrzewie a jest b
bool czy_poddrzewo(int a, int b) {
	return (order[a].first <= order[b].first) && (order[b].first <= order[a].second);
}

// lca
int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	if (czy_poddrzewo(a, b)) return a;
	
	for (int i = LOG; i >= 0; i--) {
		if (!czy_poddrzewo(skoki[b][i], a)) {
			b = skoki[b][i];
		}
	}
	
	return skoki[b][0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i < n + q; i++) {
		kra[i] = i;
		stolica[i] = i;
	}
	
	// Podzadanie 1
	if (n <= 2000 && q <= 2000) {
		int maks = n;
		for (int i = 1; i <= q; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			
			if (a == 1) {
				maks++;
				polacz(maks, b, c);
				continue;
			}
			
			if (findd(b) != findd(c)) {
				cout << "-1\n";
				continue;
			}
			for (int i = 1; i <= maks; i++) {
				odleg[i] = INF;
			}
			
			bfs(b);
			
			if (odleg[c] == INF) {
				// to nie powinno sie wypisac
				cout << "-1\n";
			} else {
				cout << odleg[c] << "\n";
			}
		}
		return 0;
	}
	
	for (int i = 1; i <= q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		zapytania[i] = make_zapytanie(a, b, c);
	}
	
	// Wygeneruj wszystkie drzewa
	int maks = n;
	for (int i = 1; i <= q; i++) {
		if (zapytania[i].typ == 1) {
			maks++;
			polacz(maks, zapytania[i].a, zapytania[i].b);
		}
	}
	
	for (int i = 1; i <= maks; i++) {
		odleg[i] = INF;
	}
	for (int i = 1; i <= maks; i++) {
		if (odleg[i] == INF) {
			int v = stolica[findd(i)];
			odleg[v] = -1;
			dfs(v, v);
		}
	}
	
	// Zniszcz polaczenia
	for (int i = 1; i <= maks; i++) {
		kra[i] = i;
		stolica[i] = i;
	}
	
	// Odpowiadamy na zapytania
	maks = n;
	for (int i = 1; i <= q; i++) {
		if (zapytania[i].typ == 1) {
			maks++;
			polacz_bez_grafu(maks, zapytania[i].a, zapytania[i].b);
			continue;
		}
		
		if (findd(zapytania[i].a) != findd(zapytania[i].b)) {
			cout << "-1\n";
			continue;
		}
		
		cout << odleg[zapytania[i].a] + odleg[zapytania[i].b] - (2 * odleg[lca(zapytania[i].a, zapytania[i].b)]) << "\n";
	}

	return 0;
}

