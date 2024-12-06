#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int LOG = 18;
int prz[MAX + 1][LOG + 1];
vector<int> graf[MAX + 1];

void dfs(int v, int p) {
	prz[v][0] = p;
	for (int i = 1; i <= LOG; i++) {
		prz[v][i] = prz[prz[v][i - 1]][i - 1];
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs(u, v);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs(1, 0);
	
	while (q--) {
		int v, k;
		cin >> v >> k;
		
		int pot = 0;
		while (k) {
			if (k & 1) {
				v = prz[v][pot];
			}
			k /= 2;
			pot++;
		}
		
		cout << (v == 0 ? -1 : v) << "\n";
	}

	return 0;
}

