#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> para;

const int INF = 1000 * 1000 * 1000;
const int MAX = 5000;
vector<para> graf[2 * MAX + 1];
int odleg[2 * MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		graf[i].push_back({i + n, a / 2});
	}
	
	int m;
	cin >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].push_back({b, c});
		graf[a + n].push_back({b + n, c});
	}
	
	for (int i = 1; i <= 2 * n; i++) {
		odleg[i] = INF;	
	}
	
	priority_queue<para, vector<para>, greater<para>> q;
	odleg[1] = 0;
	q.push({0, 1});
	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		
		for (para kraw : graf[v]) {
			int u = kraw.first;
			int w = kraw.second;
			
			if (odleg[v] + w < odleg[u]) {
				odleg[u] = odleg[v] + w;
				q.push({odleg[u], u});
			}
		}
	}
	cout << odleg[n + 1];

	return 0;
}