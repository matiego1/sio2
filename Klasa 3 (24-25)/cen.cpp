#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
int rozmiar[MAX + 1];

void dfs_rozmiar(int v, int p) {
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
	
	dfs_rozmiar(1, 1);
	cout << dfs_centroid(1, 1, rozmiar[1]);

	return 0;
}	
