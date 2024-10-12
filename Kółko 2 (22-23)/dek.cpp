#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
int rozmiar[MAX + 1];
bool czy_centroid[MAX + 1];

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

void zbuduj(int v, int p) {
	dfs_rozmiar(v, p);
	
	int centroid = dfs_centroid(v, p, rozmiar[v]);
	czy_centroid[centroid] = true;
	
	cout << centroid << " ";
	
	for (int u : graf[centroid]) {
		if (czy_centroid[u]) continue;
		zbuduj(u, centroid);
	}
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
	
	zbuduj(1, 1);

	return 0;
}


