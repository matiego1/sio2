#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
int wej[MAX + 1];
bool odwie[2][MAX + 1];
ll odleg[2][MAX + 1];
int wys[2][MAX + 1];
priority_queue<para, vector<para>, greater<para>> q;

void dijkstra(int x, int pocz) {
	odleg[x][pocz] = 0;
	wys[x][pocz] = 0;
	q.push({odleg[x][pocz], pocz});
	
	while (q.size()) {
		int v = q.top().second;
		q.pop();
		
		if (odwie[x][v]) continue;
		odwie[x][v] = true;
		
		for (int u : graf[v]) {
			if (odwie[x][u]) continue;  	  	
			
			ll nowa_odleg = odleg[x][v] + 1;
			int nowa_wys = wys[x][v] + 1;
			if (wej[u] > nowa_wys) {
				nowa_odleg += wej[u] - nowa_wys;
				nowa_wys = wej[u];
			} 
			
			if (nowa_odleg < odleg[x][u]) {
				odleg[x][u] = nowa_odleg;
				wys[x][u] = nowa_wys;
				q.push({odleg[x][u], u});
			} else if (nowa_odleg == odleg[x][u] && nowa_wys < wys[x][u]) {
				odleg[x][u] = nowa_odleg;
				wys[x][u] = nowa_wys;
				q.push({odleg[x][u], u});
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		
		odleg[0][i] = INF;
		odleg[1][i] = INF;
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dijkstra(0, 1);
	dijkstra(1, n);
	
	ll wynik = LLONG_MAX;
	for (int i = 1; i <= n; i++) {
		wynik = min(wynik, odleg[0][i] + odleg[1][i] + max(0, abs(wys[0][i] - wys[1][i]) - 1));
	}
	cout << wynik;

	return 0;
}

