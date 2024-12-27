#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
map<ll, ll> dp[MAX + 1];
ll wej[MAX + 1];

void dfs(int v, ll k) {
	if (dp[v].find(k) != dp[v].end()) return;
	
	dp[v][k] = wej[v] * k;

	int m = (int) graf[v].size();
	if (m == 0) return;
	
	vector<ll> wart;
	for (int u : graf[v]) {
		ll f = k / m;
		ll c = (k + m - 1) / m;
		
		dfs(u, f);
		dfs(u, c);
		
		dp[v][k] += dp[u][f];
		wart.push_back(dp[u][c] - dp[u][f]);
	}
	
	sort(wart.begin(), wart.end(), greater());
	
	for (int i = 0; i < (int) k % m; i++) {
		dp[v][k] += wart[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		graf[a].push_back(i);
		cin >> wej[i];
	}
	
	dfs(1, k);
	cout << dp[1][k];

	return 0;
}

