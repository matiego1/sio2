#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
const int INF = 1000 * 1000 * 1000;

int grupy[MAX + 1];
vector<int> graf[MAX + 1];
ll dp[MAX + 1];

void dfs(int v, int p) {
    dp[v] = dp[p] * max(1, (int) graf[v].size() - 1);
    if (dp[v] > INF) dp[v] = 0;
    
    for (int u : graf[v]) {
    	if (u == p) continue;
    	dfs(u, v);
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, g, k;
    cin >> n >> g >> k;

    for (int i = 1; i <= g; i++) {
        cin >> grupy[i];
    }
    sort(grupy + 1, grupy + 1 + g);

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;

        if (i == 1) {
            graf[a].push_back(0);
            graf[0].push_back(a);
            graf[b].push_back(0);
            graf[0].push_back(b);
        } else {
            graf[a].push_back(b);
            graf[b].push_back(a);
        }
    }

	dp[0] = 1;
    dfs(0, 0);
    
    ll wynik = 0;
    for (int i = 1; i <= n; i++) {
    	if (graf[i].size() != 1) continue;
    	
    	ll mini = dp[i] * k;
    	ll maks = dp[i] * (k + 1) - 1;
    	
    	int pocz = lower_bound(grupy + 1, grupy + 1 + g, mini) - grupy;
    	int kon = upper_bound(grupy + 1, grupy + 1 + g, maks) - grupy - 1;
    	
    	wynik += max(0, kon - pocz + 1);
	}
	cout << wynik * k;

    return 0;
}
