#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
const int R = (1 << 20);
vector<int> graf[MAX + 1];
para order[MAX + 1];
int tree[2 * R];
int t = 0;

void dodaj(int indeks) {
	indeks += R;
	tree[indeks] = 1;
	while (indeks > 1) {
		indeks /= 2;
		tree[indeks] = tree[2 * indeks] + tree[2 * indeks + 1];
	}
}

int query(int pocz, int kon) {
	pocz += R;
	kon += R;
	int wynik = tree[pocz];
	if (pocz != kon) wynik += tree[kon];
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

void dfs(int v, int p) {
	order[v].first = ++t;
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs(u, v);
	}
	order[v].second = t;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs(1, 1);
	
	for (int i = 1; i <= n; i++) {
		printf("%d\n", query(order[i].first, order[i].second));
		dodaj(order[i].first);
	}
	return 0;
}
