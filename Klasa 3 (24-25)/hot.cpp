#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000 + 5;
vector<para> graf[MAX];
vector<int> graf2[MAX];
vector<int> graf3[MAX];
bool odwie[MAX];
int order[MAX];
int sklad[MAX];
ll odleg[MAX];
int dp[MAX];
int poziom[MAX];
int odp[MAX];
queue<int> kolejka;
int t = 0;

int mod(int a, int b) {
	int w = a % b;
	return w >= 0 ? w : w + b;
}

void dfs(int v) {
	odwie[v] = true;
	for (para u : graf[v]) {
		if (odwie[u.first]) continue;
		dfs(u.first);
	}
	order[++t] = v;
}

void sss(int v) {
	odwie[v] = true;
	sklad[v] = t;
	for (int u : graf2[v]) {
		if (odwie[u]) continue;
		sss(u);
	}
}

void dfs_odleg(int v, ll akt, int skladowa) {
	odleg[v] = akt;
	odwie[v] = true;
	for (para& p : graf[v]) {
		if (sklad[p.first] != skladowa) continue;
		if (odwie[p.first]) continue;
		dfs_odleg(p.first, akt + p.second, skladowa);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		int c = mod(a + b, n);
		a = mod(a, n);
		graf[a].push_back({c, b});
		graf2[c].push_back(a);
	}
	
	for (int i = 0; i < n; i++) {
		if (odwie[i]) continue;
		dfs(i);
	}
	
	t = 0;
	for (int i = 0; i < n; i++) odwie[i] = false;
	for (int i = n; i >= 1; i--) {
		if (odwie[order[i]]) continue;
		t++;
		sss(order[i]);
	}
	
	for (int i = 0; i < n; i++) graf2[i].clear();
	
	for (int i = 0; i < n; i++) {
		for (para p : graf[i]) {
			if (sklad[i] != sklad[p.first]) {
				graf2[sklad[i]].push_back(sklad[p.first]);
				graf3[sklad[p.first]].push_back(sklad[i]);
			}
		}
	}
	
	for (int i = 0; i < n; i++) odwie[i] = false;
	for (int i = 0; i < n; i++) {
		if (odwie[i]) continue;
		dfs_odleg(i, 0, sklad[i]);
	}
	
	for (int i = 0; i < n; i++) {
		for (para p : graf[i]) {
			if (sklad[i] != sklad[p.first]) continue;
			if (odleg[i] + p.second == odleg[p.first]) continue;
			dp[sklad[i]] = 1;
		}
	}
	
	for (int i = 1; i <= t; i++) {
		poziom[i] = (int) graf2[i].size();
		if (poziom[i] == 0) {
			kolejka.push(i);
		}
	}
	
	while (kolejka.size()) {
		int v = kolejka.front();
		kolejka.pop();
		
		for (int u : graf2[v]) {
			dp[v] += dp[u];
		}
		
		for (int u : graf3[v]) {
			poziom[u]--;
			if (poziom[u] == 0) {
				kolejka.push(u);
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		odp[i] = (dp[sklad[i]] > 0);
	}
	
	while (q--) {
		int x;
		cin >> x;
		cout << (odp[mod(x, n)] ? "Yes" : "No") << "\n";
	}

	return 0;
}
