#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int MAX = 5 * 100 * 1000;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
vector<para> graf[2 * MAX + 1];
ll odleg[2 * MAX + 1];
vector<int> cele;

int main() {
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	
	int n, m;
	scanf("%d %d", &n, &m);
//	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
//		cin >> a >> b >> c;
		
		if (c % 2 == 0) {
			graf[a].push_back(make_pair(b, c));
			graf[b].push_back(make_pair(a, c));
			
			graf[a + n].push_back(make_pair(b + n, c));
			graf[b + n].push_back(make_pair(a + n, c));
		} else {
			graf[a].push_back(make_pair(b + n, c));
			graf[b + n].push_back(make_pair(a, c));
			
			graf[a + n].push_back(make_pair(b, c));
			graf[b].push_back(make_pair(a + n, c));
		}
	}
	
	for (int i = 1; i <= 2 * n; i++) {
		odleg[i] = INF;
	}
	
	priority_queue<para, vector<para>, greater<para>> q;
	q.push(make_pair(0, 1));
	while (!q.empty()) {
		int v = q.top().second;
		ll d = q.top().first;
		q.pop();
		
		if (odleg[v] <= d) continue;
		odleg[v] = d;
		
		for (para p : graf[v]) {
			q.push(make_pair(odleg[v] + p.second, p.first));
		}
	}
	
	ll wynik = -1;
	for (int i = 1; i <= n; i++) {
		if (odleg[i] == INF || odleg[i + n] == INF) continue;
		if (odleg[i] == odleg[i + n]) continue;
		
		wynik = max(wynik, odleg[i] + odleg[i + n]);
	}
	
	for (int i = 1; i <= n; i++) {
		if (odleg[i] + odleg[i + n] == wynik) {
			cele.push_back(i);
		}
	}
	
	if (cele.empty()) {
		printf("BRAK");
//		cout << "BRAK";
		return 0;
	}
	
	for (int v : cele) {
		printf("%d ", v);
//		cout << v << " ";
	}
	printf("\n%lld", wynik);
//	cout << "\n" << wynik;

	return 0;
}
