#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 1000 * 1000;
const int MOD = 1000 * 1000 * 1000 + 9;
vector<int> graf[MAX + 1];
int DP[MAX + 1];
int topo[MAX + 10];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, pocz, kon;
	cin >> n >> m >> pocz >> kon;
	
	if (pocz == kon) {
		cout << 0;
		return 0;
	}
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		if (b != pocz) {
			graf[a].push_back(b);
			DP[b]++;
		}
	}
	
	int q_pocz = 2, q_kon = 2;
	topo[q_kon] = pocz;
	for (int i = 1; i <= n; i++) {
		if (DP[i] == 0 && i != pocz) {
			topo[++q_kon] = i;
		}
	}
	
	int indeks = 0;
	while (q_pocz <= q_kon) {
		int akt = topo[q_pocz];
		q_pocz++;
		topo[++indeks] = akt;
		for (int u : graf[akt]) {
			DP[u]--;
			if (DP[u] <= 0) {
				topo[++q_kon] = u;
			}
		}
	}
	
	if (pocz == kon) {
		cout << 0;
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		DP[i] = 0;
	}
	
	DP[kon] = 1;
	for (int i = indeks; i >= 1; i--) {
		if (topo[i] == kon) continue;
		for (int u : graf[topo[i]]) {
			DP[topo[i]] = (DP[topo[i]] + DP[u]) % MOD;
		}
	}
	cout << DP[pocz];
	
	return 0;
}