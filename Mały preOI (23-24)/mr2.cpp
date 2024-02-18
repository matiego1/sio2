#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

struct Trasa {
	int a, b, osoby, koszt;
};
struct Zapyt {
	int a, b, osoby, indeks;
};
Trasa make_trasa(int a, int b, int osoby, int koszt) {
	return {a, b, osoby, koszt};
}
Zapyt make_zapyt(int a, int b, int osoby, int indeks) {
	return {a, b, osoby, indeks};
}

const int MAX = 5 * 100 * 1000;
const int LOG = 19;
const int R = (1 << LOG);

Trasa trasy[MAX + 1];
Zapyt zapytania[MAX + 1];
vector<int> graf[MAX + 1];
para order[MAX + 1];
int t = 0;
int skok[MAX + 1][LOG + 1];
ll tree[2 * R];
ll wynik[MAX + 1];

void dfs(int v, int ojciec) {
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

bool czy_poddrzewo(int a, int b) { // czy w poddrzewie a jest b
	return (order[a].first <= order[b].first) && (order[b].first <= order[a].second);
}

int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	
	for (int i = LOG; i >= 0; i--) {
		if (!czy_poddrzewo(skok[b][i], a)) {
			b = skok[b][i];
		}
	}
	
	return skok[b][0];
}

void update(int a, int b, int x) {
	a += R;
	b += R;
	
	tree[a] += x;
	if (a != b) {
		tree[b] += x;
	}
	
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			tree[a + 1] += x;
		}
		if (b % 2 == 1) {
			tree[b - 1] += x;
		}
		
		a /= 2;
		b /= 2;
	}
}

ll query(int i) {
	i += R;
	
	ll wynik = 0;
	while (i >= 1) {
		wynik += tree[i];
		i /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i < n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		trasy[i] = make_trasa(a, b, c, d);
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	for (int i = 1; i <= q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		zapytania[i] = make_zapyt(a, b, c, i);
	}
	
	sort(trasy + 1, trasy + n, [](Trasa& a, Trasa& b) { return a.osoby < b.osoby; });
	sort(zapytania + 1, zapytania + q + 1, [](Zapyt& a, Zapyt& b) { return a.osoby < b.osoby; });
	
	dfs(1, 1);
	
	int j = 1;
	for (int i = 1; i <= q; i++) {
		while (j < n && zapytania[i].osoby >= trasy[j].osoby) {
			if (czy_poddrzewo(trasy[j].b, trasy[j].a)) {
				swap(trasy[j].a, trasy[j].b);
			}
			update(order[trasy[j].b].first, order[trasy[j].b].second, trasy[j].koszt);
			j++;
		}
		
		wynik[zapytania[i].indeks] = query(order[zapytania[i].a].first) + query(order[zapytania[i].b].first) - (2 * query(order[lca(zapytania[i].a, zapytania[i].b)].first));
	}
	
	for (int i = 1; i <= q; i++) {
		cout << wynik[i] << "\n";
	}

	return 0;
}

