#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Zapyt {
	char typ;
	int a, b;
};

const int MAX = 200 * 1000;
const int R = (1 << 18);
vector<int> graf[MAX + 1];
vector<int> poziomy[MAX + 1];
Zapyt zapyt[MAX + 1];
para order[MAX + 1];
int gleb[MAX + 1];
int tree[2 * R];
int indeks_poz[MAX + 1];
int indeks_tree[MAX + 1];
int t = 0;

void dfs(int v, int g) {
	gleb[v] = g;
	order[v].first = (++t);
	
	poziomy[g].push_back(order[v].first);
	indeks_poz[v] = (int) poziomy[g].size() - 1;
	
	for (int u : graf[v]) {
		dfs(u, g + 1);
	}
	
	order[v].second = t;
}

void wlacz(int v) {
	int i = indeks_tree[gleb[v]] + indeks_poz[v];
	i += R;
	
	tree[i] = 1;
	while (i > 1) {
		i /= 2;
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}

int query(int pocz, int kon) {
	pocz += R;
	kon += R;
	
	int wynik = tree[pocz];
	if (pocz != kon) {
		wynik += tree[kon];
	}
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik += tree[pocz + 1];
		}
		if (kon % 2 == 1) {
			wynik += tree[kon - 1];
		}
		pocz /= 2;
		kon /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int q;
	cin >> q;
	
	for (int i = 1; i <= q; i++) {
		char typ;
		cin >> typ;
		int a, b;
		cin >> a >> b;
		
		zapyt[i] = {typ, a, b};
		
		if (typ == 'Z') {
			graf[b].push_back(a);
		}
	}
	
	dfs(1, 1);
	
	int indeks = 1;
	for (int g = 1; g <= MAX; g++) {
		if (poziomy[g].empty()) continue;
		
		indeks_tree[g] = indeks;
		indeks += (int) poziomy[g].size();
	}
	
	wlacz(1);
	for (int i = 1; i <= q; i++) {
		Zapyt& z = zapyt[i];
		
		if (z.typ == 'Z') {
			wlacz(z.a);
		} else {
			int g = gleb[z.a] + z.b + 1;
			
			int pocz = lower_bound(poziomy[g].begin(), poziomy[g].end(), order[z.a].first, [](int& x, int mini) {
				return x < mini;
			}) - poziomy[g].begin();
			
			int kon = upper_bound(poziomy[g].begin(), poziomy[g].end(), order[z.a].second, [](int maks, int& x) {
				return maks < x;
			}) - poziomy[g].begin() - 1;
			
			if (pocz > kon) {
				cout << "0\n";
				continue;
			}
			
			pocz += indeks_tree[g];
			kon += indeks_tree[g];
			
			cout << query(pocz, kon) << "\n";
		}
	}

	return 0;
}

