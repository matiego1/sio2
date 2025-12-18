#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, ll> para;

const int MAX = 1000 * 1000;
vector<para> graf[MAX + 1];
ll wej[MAX + 1];
ll dp[MAX + 1];
bool odwie[MAX + 1];
bool wynik = true;
int order[MAX + 1];
int low[MAX + 1];
set<para> mosty;
int t = 0;

void dfs_low(int v, int p) {
	odwie[v] = true;
	order[v] = ++t;
	low[v] = t;
	bool byl_ojciec = false;
	for (para u : graf[v]) {
		if (u.first == p && !byl_ojciec) {
			byl_ojciec = true;
			continue;
		}
		if (odwie[u.first]) {
			low[v] = min(low[v], order[u.first]);
		} else {
			dfs_low(u.first, v);
			low[v] = min(low[v], low[u.first]);
			if (low[u.first] > order[v]) {
				mosty.insert({v, u.first});
				mosty.insert({u.first, v});
//				cout << "MOST " << v << " " << u.first << "\n";
			}
		}
	}
}

void dfs(int v) {
	dp[v] = wej[v];
	odwie[v] = true;
	for (para u : graf[v]) {
		if (odwie[u.first]) continue;
		dfs(u.first);
		if (abs(dp[u.first]) > u.second && mosty.find({v, u.first}) != mosty.end()) wynik = false;
		dp[v] += dp[u.first];
	}
}

bool rozwiaz() {
	int n, m;
	cin >> n >> m;
	
	wynik = true;
	t = 0;
	mosty.clear();
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		
		graf[i].clear();
		odwie[i] = false;
		low[i] = 0;
		order[i] = 0;
		dp[i] = 0;
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		graf[a].push_back({b, c});
		graf[b].push_back({a, c});
	}
	
	dfs_low(1, 0);
	for (int i = 1; i <= n; i++) odwie[i] = false;
	dfs(1);
	
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	
	while (T--) {
		cout << (rozwiaz() ? "TAK\n" : "NIE\n");
	}

	return 0;
}
