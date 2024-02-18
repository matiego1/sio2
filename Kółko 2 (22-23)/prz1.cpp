#include <iostream>
#include <vector>
#include <queue>
#define pb push_back
using namespace std;
const int MAX = 5000 * 2;
const int INF = (1 << 30);

vector<pair<int, int>> graf[MAX + 5];


int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        graf[i].pb(make_pair(n + i, a / 2));
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graf[a].pb(make_pair(b, c));
        graf[a + n].pb(make_pair(b + n, c));
    }

    int dist[MAX + 5];
    for (int i = 0; i < MAX + 5; i++) {
        dist[i] = INF;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[1] = 0;
    pq.push(make_pair(0, 1));

    while(!pq.empty()){
		int u = pq.top().second;
        int o = pq.top().first;
		pq.pop();

		if (o > dist[u]) {
            continue;
		}

		for(auto x : graf[u]){
			int v = x.first;
			int w = x.second;

			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
    }

    cout << dist[n + 1];

    return 0;
}
