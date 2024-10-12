#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
int rozmiar[MAX + 1];
bool czy_centroid[MAX + 1];
int k;

void dfs_rozmiar(int v, int p) {
	rozmiar[v] = 1;
	for (int u : graf[v]) {
		if (czy_centroid[u]) continue;
		if (u == p) continue;
		dfs_rozmiar(u, v);
		rozmiar[v] += rozmiar[u];
	}
}

int dfs_centroid(int v, int p, int n) {
	for (int u : graf[v]) {
		if (czy_centroid[u]) continue;
		if (u == p) continue;
		if (rozmiar[u] > n / 2) {
			return dfs_centroid(u, v, n);			
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
	
	if (rozmiar[v] <= k) return 0;
	
	int centroid = dfs_centroid(v, p, rozmiar[v]);
	czy_centroid[centroid] = true;
	
	ll wynik = 0;
	vector<int> wszystkie(1, 1);
	for (int u : graf[centroid]) {
		if (czy_centroid[u]) continue;
		
		vector<int> poziomy(1);
		dfs_poziomy(u, centroid, 1, poziomy);
		
		for (int i = 1; i < min((int) poziomy.size(), k + 1); i++) {
			if (k - i < (int) wszystkie.size()) {
				wynik += (ll) poziomy[i] * wszystkie[k - i];
			}
		}
		
		for (int i = 1; i < min((int) poziomy.size(), k); i++) {
			if (i >= (int) wszystkie.size()) wszystkie.push_back(0);
			wszystkie[i] += poziomy[i];
		}
		
		wynik += zbuduj(u, centroid);
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n >> k;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	cout << zbuduj(1, 1);

	return 0;
}


