#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
int rozmiar[MAX + 1];
bool czy_centroid[MAX + 1];
int n, k_min, k_max;

ll query(unordered_map<int, int>& tree, int i) {
	ll wynik = 0;
	for (; i >= 0; i = (i & (i + 1)) - 1) {
		wynik += tree[i];
	}
	return wynik;
}

ll query(unordered_map<int, int>& tree, int pocz, int kon) {
	return query(tree, kon) - query(tree, pocz - 1);
}

void dodaj(unordered_map<int, int>& tree, int i, int wart) {
	for (; i < n; i = i | (i + 1)) {
		tree[i] += wart;
	}
}

void dfs_rozmiar(int v, int p) {
	rozmiar[v] = 1;
	for (int u : graf[v]) {
		if (czy_centroid[u]) continue;
		if (u == p) continue;
		dfs_rozmiar(u, v);
		rozmiar[v] += rozmiar[u];
	}
}

int dfs_centroid(int v, int p, int roz) {
	for (int u : graf[v]) {
		if (czy_centroid[u]) continue;
		if (u == p) continue;
		if (rozmiar[u] > roz / 2) {
			return dfs_centroid(u, v, roz);
		}
	}
	return v;
}

void dfs_poziomy(int v, int p, int poziom, vector<int>& poziomy) {
	if (poziom >= (int) poziomy.size()) poziomy.push_back(0);
	
	poziomy[poziom]++;
	for (int u : graf[v]) {
		if (czy_centroid[u]) continue;
		if (u == p) continue;
		dfs_poziomy(u, v, poziom + 1, poziomy);
	}
}

ll zbuduj(int v, int p) {
	dfs_rozmiar(v, p);
	
	if (rozmiar[v] <= k_min) return 0;
	
	int centroid = dfs_centroid(v, p, rozmiar[v]);
	czy_centroid[centroid] = true;
	
	unordered_map<int, int> wszystkie;
	dodaj(wszystkie, 0, 1);
	
	ll wynik = 0;
	for (int u : graf[centroid]) {
		if (czy_centroid[u]) continue;
		
		vector<int> poziomy(1);
		dfs_poziomy(u, centroid, 1, poziomy);
		
		for (int i = 1; i < min((int) poziomy.size(), k_max + 1); i++) {
			int pocz = max(0, k_min - i);
			int kon = min((int) wszystkie.size() - 1, k_max - i);
			ll suma = query(wszystkie, pocz, kon);
			wynik += suma * poziomy[i];
		}
		
		for (int i = 1; i < min((int) poziomy.size(), k_max); i++) {
			dodaj(wszystkie, i, poziomy[i]);
		}
		
		wynik += zbuduj(u, centroid);
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k_min >> k_max;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	cout << zbuduj(1, 1);

	return 0;
}
