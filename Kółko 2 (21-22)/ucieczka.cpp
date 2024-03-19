#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int INF = 2 * 1000 * 1000 * 1000;

vector<para> graf[MAX + 1];
bool wynik[MAX + 1];
int odleg[MAX + 1];
vector<int> poprzednik[MAX + 1];
priority_queue<para, vector<para>, greater<para>> q;

void dfs(int v) {
	wynik[v] = true;
	for (int u : poprzednik[v]) {
		dfs(u);
	}
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
		graf[b].push_back({a, c});
	}
	
	for (int i = 1; i <= n; i++) {
		odleg[i] = INF;
	}
	odleg[1] = 0;
	
	q.push({0, 1});
	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		
		for (para p : graf[v]) {
			int u = p.first, w = p.second;
			if (odleg[u] > odleg[v] + w) {
				odleg[u] = odleg[v] + w;
				poprzednik[u] = {v};
				q.push({odleg[u], u});
			} else if (odleg[u] == odleg[v] + w) {
				poprzednik[u].push_back(v);
			}
 		}
	}
	
	dfs(n);
	
	for (int i = 1; i <= n; i++) {
		if (wynik[i]) {
			cout << i << "\n";
		}
	}

	return 0;
}


