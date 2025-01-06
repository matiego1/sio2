#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
ll dp[MAX + 1];

void dfs(int v, int p) {
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs(u, v);
		dp[v] += dp[u];
	}
	dp[v] = max(dp[v], 1ll);
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
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << dp[a] * dp[b] << "\n";
	}

	return 0;
}

