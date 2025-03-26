#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
vector<para> graf[MAX + 1];
vector<para> graf2[MAX + 1];
vector<int> graf3[MAX + 1];
bool odwie[MAX + 1];
int order[MAX + 1];
int sklad[MAX + 1];
int poziom[MAX + 1];
ll dp[MAX + 1];
int t = 0;
queue<int> q;

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
	for (para u : graf2[v]) {
		if (odwie[u.first]) continue;
		sss(u.first);
	}
}

ll koszt_drogi(ll w) {
	ll pocz = 1, kon = 15000;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (w > srodek * (srodek + 1) / 2) {
			pocz = srodek + 1;
		} else {
			kon = srodek;
		}
	}
	
	ll k = pocz;
	return w * k - k * k * (k - 1) / 2 + k * (k - 1) * (2 * k - 1) / 6;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].push_back({b, c});
		graf2[b].push_back({a, c});
	}
	
	for (int i = 1; i <= n; i++) {
		if (odwie[i]) continue;
		dfs(i);
	}
	
	t = 0;
	for (int i = 1; i <= n; i++) odwie[i] = false;
	for (int i = n; i >= 1; i--) {
		if (odwie[order[i]]) continue;
		t++;
		sss(order[i]);
	}
	
	for (int i = 1; i <= n; i++) graf2[i].clear();
	for (int i = 1; i <= n; i++) {
		for (para p : graf[i]) {
			if (sklad[i] == sklad[p.first]) {
				dp[sklad[i]] += koszt_drogi(p.second);
			} else {
				graf2[sklad[i]].push_back({sklad[p.first], p.second});
				graf3[sklad[p.first]].push_back(sklad[i]);
				poziom[sklad[i]]++;
			}
		}
	}
	
	for (int i = 1; i <= t; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		ll maks = 0;
		for (para u : graf2[v]) {
			maks = max(maks, dp[u.first] + u.second);
		}
		dp[v] += maks;
		
		for (int p : graf3[v]) {
			poziom[p]--;
			if (poziom[p] == 0) {
				q.push(p);
			}
		}
	}
	
	int start;
	cin >> start;
	cout << dp[sklad[start]];

	return 0;
}

