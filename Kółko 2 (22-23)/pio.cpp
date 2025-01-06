#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
vector<int> graf2[MAX + 1];
int wej[MAX + 1];
int poziom[MAX + 1];
int dp[MAX + 1];
int odleg[MAX + 1];
queue<int> q;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;
	
	
	for (int i = 1; i <= k; i++) {
		cin >> wej[i];
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf2[b].push_back(a);
		poziom[a]++;
	}
	
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		for (int p : graf2[v]) {
			poziom[p]--;
			if (poziom[p] == 0) {
				q.push(p);
			}
		}
		
		int maks = 0, mini = INT_MAX;
		for (int u : graf[v]) {
			if (dp[u]) {
				maks = max(maks, odleg[u] + 1);
			} else {
				dp[v] = true;
				mini = min(mini, odleg[u] + 1);
			}
		}
		
		if (dp[v]) {
			odleg[v] = mini;
		} else {
			odleg[v] = maks;
		}
	}
	
	int mini_wygry = INT_MAX;
	for (int i = 1; i <= k; i++) {
		if (dp[wej[i]]) mini_wygry = min(mini_wygry, odleg[wej[i]]);
	}
	
	for (int i = 1; i <= k; i++) {
		if (dp[wej[i]]) continue;
		if (odleg[wej[i]] >= mini_wygry) continue;
		cout << "R";
		return 0;
	}
	
	cout << "T";
	
	return 0;
}
