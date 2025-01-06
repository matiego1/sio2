#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int MOD = 1000 * 1000 * 1000 + 7;
vector<int> graf[MAX];
int wej[MAX];
ll dp[MAX][2];

ll odwrotnosc(ll a) {
	ll b = MOD - 2, wynik = 1;
	while (b) {
		if (b & 1) {
			wynik = wynik * a % MOD;
		}
		a = a * a % MOD;
		b /= 2;
	}
	return wynik;
}

void dfs(int v, int p) {
	dp[v][0] = 1;
	dp[v][1] = 0;
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs(u, v);
		
		dp[v][0] = dp[v][0] * dp[u][0] % MOD;
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		
		dp[v][1] = (dp[v][1] + dp[v][0] * dp[u][1] % MOD * odwrotnosc(dp[u][0]) % MOD) % MOD;
	}
	
	if (wej[v]) {
		dp[v][1] = dp[v][0];
	} else {
		dp[v][0] = (dp[v][0] + dp[v][1]) % MOD;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n - 1; i++) {
		int a;
		cin >> a;
		graf[i].push_back(a);
		graf[a].push_back(i);
	}
	
	for (int i = 0; i < n; i++) {
		cin >> wej[i];
	}
	
	dfs(0, 0);
	
	cout << dp[0][1];

	return 0;
}

