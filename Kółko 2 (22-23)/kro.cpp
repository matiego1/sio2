#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
set<int> graf[MAX + 1];
int rozmiar[MAX + 1];
int poziom[MAX + 1];

void dfs_rozmiar(int v, int p) {
	poziom[v] = poziom[p] + 1;
	rozmiar[v] = 1;
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs_rozmiar(u, v);
		rozmiar[v] += rozmiar[u];
	}
}

int dfs_centroid(int v, int p, int n) {
	for (int u : graf[v]) {
		if (u == p) continue;
		if (rozmiar[u] > n / 2) {
			return dfs_centroid(u, v, n);
		}
	}
	return v;
}

bool czy_centroid(int v, int n) {
	for (int u : graf[v]) {
		if (poziom[u] < poziom[v] && n - rozmiar[v] > n / 2) return false;
		if (poziom[u] > poziom[v] && rozmiar[u] > n / 2) return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].insert(b);
		graf[b].insert(a);
	}
	
	dfs_rozmiar(1, 1);
	int centroid = dfs_centroid(1, 1, n);
	
	int wynik_v = centroid, wynik = graf[centroid].size();
	for (int u : graf[centroid]) {
		if (!czy_centroid(u, n)) continue;
		if ((int) graf[u].size() > wynik) {
			wynik = graf[u].size();
			wynik_v = u;
		}
	}
	cout << wynik_v << "\n" << wynik;

	return 0;
}


