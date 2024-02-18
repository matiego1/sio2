#include <iostream>
#include <vector>
#include <tuple>
#include "slo.h"
using namespace std;

const int MAX = 100 * 1000;
const int LOG = 17;
const int R = (1 << LOG);

struct Info {
	vector<pair<int, int>> kra;
	int order;
	int maxOrder;
	int prz[LOG];
	int h = 0;
};
Info graf[MAX + 1];
long long tree[2 * R];
int t = 0;

void dfs(int v, int p, int odleglosc) {
	graf[v].order = ++t;
	
	tree[t + R] = odleglosc;
	
	graf[v].prz[0] = p;
	for (int k = 1; k < LOG; k++) {
		graf[v].prz[k] = graf[graf[v].prz[k - 1]].prz[k - 1];
	}
	
	for (pair<int, int> u : graf[v].kra) {
		if (u.first != p) {
			graf[u.first].h = graf[v].h + 1;
			dfs(u.first, v, odleglosc + u.second);
		}
	}
	
	graf[v].maxOrder = t;
}

//czy w poddrzewie a jest b
bool czy_poddrzewo(int a, int b) {
	return graf[a].order <= graf[b].order && graf[b].order <= graf[a].maxOrder;
}

int lca(int a, int b) {
	if (czy_poddrzewo(b, a)) return b;
	
	for (int k = LOG - 1; k >= 0; k--) {
		if (!czy_poddrzewo(graf[b].prz[k], a)) {
			b = graf[b].prz[k];
		}
	}
	
	return graf[b].prz[0];
}

long long odleglosc(int v) {
	v = graf[v].order;
	v += R;
	long long wynik = 0;
	while (v > 0) {
		wynik += tree[v];
		v /= 2;
	}
	return wynik;
}

void init(vector<tuple<int, int, int>> edges) {
	for (tuple<int, int, int> edge : edges) {
		graf[get<0>(edge)].kra.push_back(make_pair(get<1>(edge), get<2>(edge)));
		graf[get<1>(edge)].kra.push_back(make_pair(get<0>(edge), get<2>(edge)));
	}
	dfs(1, 1, 0);
}
int distance(int a, int b) {
	return odleglosc(a) + odleglosc(b) - 2 * odleglosc(lca(a, b));
}
void change(int a, int b, int c) {
	c -= distance(a, b);
	if (graf[b].h > graf[a].h) swap(a, b);
	
	b = graf[a].maxOrder;
	a = graf[a].order;
	
	a += R;
	b += R;
	tree[a] += c;
	if (a != b) {
		tree[b] += c;
	}
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			tree[a + 1] += c;
		}
		if (b % 2 == 1) {
			tree[b - 1] += c;
		}
		a /= 2;
		b /= 2;
	}
}
