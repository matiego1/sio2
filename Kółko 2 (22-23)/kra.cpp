#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 1000 * 1000;
const int MOD = 1000 * 1000 * 1000 + 9;
vector<int> graf[MAX + 1];
int poziom[MAX + 1];
int DP[MAX + 1]; 

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
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int u : graf[i]) {
			poziom[u]++;
		}
	}
	
	queue<int> q;
	q.push(pocz);
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0 && i != pocz) {
			q.push(i);
		} 
	}
	
	vector<int> topo;
	while (!q.empty()) {
		int akt = q.front();
		q.pop();
		topo.push_back(akt);
		for (int u : graf[akt]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
	}
	reverse(topo.begin(), topo.end());
	
	if (pocz == kon) {
		cout << 0; // ?????????
		return 0;
	}
	
	DP[kon] = 1;
	for (int v : topo) {
		if (v == kon) continue;
		for (int u : graf[v]) {
			DP[v] = (DP[v] + DP[u]) % MOD;
		}
	}
	cout << DP[pocz];
	
	return 0;
}
