#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int MAX = 200 * 1000;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
vector<para> graf[MAX + 1];
ll odleg[2][MAX + 1];
ll od_pocz[MAX + 1];
ll od_kon[MAX + 1];
set<para> q;

void dijkstra(ll n, ll pocz, ll indeks) {
	for (int i = 1; i <= n; i++) odleg[indeks][i] = INF;
	odleg[indeks][pocz] = 0;
	q.insert({0, pocz});
	while (q.size()) {
		auto pierwszy = q.begin();
		q.erase(pierwszy);
		ll v = pierwszy->second;
		for (para p : graf[v]) {
			ll u = p.first;
			ll w = p.second;
			if (odleg[indeks][u] > odleg[indeks][v] + w) {
				q.erase({odleg[indeks][u], u});
				odleg[indeks][u] = odleg[indeks][v] + w;
				q.insert({odleg[indeks][u], u});
			}
		}
	}
}

int main() {
	ll n, m;
	scanf("%lld %lld", &n, &m);
	
	ll start, meta, c, k;
	scanf("%lld %lld %lld %lld", &start, &meta, &c, &k);
	
	for (int i = 1; i <= m; i++) {
		ll a, b, w;
		scanf("%lld %lld %lld", &a, &b, &w);
		graf[a].push_back({b, w});
		graf[b].push_back({a, w});
	}
	
	dijkstra(n, start, 0);
	dijkstra(n, meta, 1);
	
	if (odleg[0][meta] <= k) {
		printf("%lld", n * (n - 1) / 2);
		return 0;
	}
	if (c > k) {
		putchar('0');
		return 0;
	}
	if (c == k) {
		putchar('1');
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		od_pocz[i] = odleg[0][i];
		od_kon[i] = odleg[1][i];
	}
	
	sort(od_pocz + 1, od_pocz + 1 + n);
	sort(od_kon + 1, od_kon + 1 + n);
	
	ll wynik = 0, indeks = 0;
	for (int i = n; i >= 1; i--) {
		while (od_pocz[indeks] <= k - c - od_kon[i]) indeks++;
		wynik += max(0ll, indeks - 1);
	}
	printf("%lld", wynik);

	return 0;
}
