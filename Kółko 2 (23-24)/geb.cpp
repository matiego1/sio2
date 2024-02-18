#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll, int> para;

const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX = 2 * 100 * 1000;
vector<para> graf[MAX + 1];
ll odleg[MAX + 1];
int cel[MAX + 1];
ll atrakcyjnosc[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[b].push_back({a, c});
	}
	
	atrakcyjnosc[0] = INF;
	for (int i = 1; i <= n; i++) {
		odleg[i] = INF;
	}
	
	priority_queue<para, vector<para>, greater<para>> q;
	for (int i = 1; i <= k; i++) {
		int a;
		cin >> a;
		
		if (atrakcyjnosc[a] != 0) continue;
		atrakcyjnosc[a] = i;
		
		cel[a] = a;
		odleg[a] = 0;
		q.push({0, a});
	}

	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		
		for (para kraw : graf[v]) {
			int u = kraw.first;
			int w = kraw.second;
			if (odleg[u] > odleg[v] + w) {
				odleg[u] = odleg[v] + w;
				cel[u] = cel[v];
				q.push({odleg[u], u});
			}
			if (odleg[u] == odleg[v] + w && atrakcyjnosc[cel[v]] < atrakcyjnosc[cel[u]]) {
				cel[u] = cel[v];
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << (cel[i] == 0 ? -1 : cel[i]) << " ";
	}

	return 0;
}

