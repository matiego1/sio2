#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Krawedz {
	int v, u;
	ll waga;
};

const ll INF = LLONG_MAX;
const int PREC = 1000;
const int MAX_N = 100;
const int MAX_M = 10 * 1000;
int n, m;
Krawedz krawedzie[MAX_M + 1];
ll odleg[MAX_N + 1][MAX_N + 1];

bool czy_ujemny_cykl(ll x) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			odleg[i][j] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		odleg[i][i] = 0;
	}
	
	for (int i = 1; i <= m; i++) {
		odleg[krawedzie[i].v][krawedzie[i].u] = min(odleg[krawedzie[i].v][krawedzie[i].u], krawedzie[i].waga + x);
	}
	
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			if (odleg[i][k] >= INF) continue;
			for (int j = 1; j <= n; j++) {
				if (odleg[k][j] >= INF) continue;
				odleg[i][j] = min(odleg[i][j], odleg[i][k] + odleg[k][j]);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (odleg[i][i] < 0) {
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(3);
	
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, c * PREC};
	}
	
	if (czy_ujemny_cykl(0)) {
		ll pocz = 1, kon = 1000ll * 1000 * 1000 * PREC;
		while (pocz < kon) {
			ll srodek = (pocz + kon) / 2;
			if (czy_ujemny_cykl(srodek)) {
				pocz = srodek + 1;
			} else {
				kon = srodek;
			}
		}
		cout << -((long double) pocz) / PREC;
		
		return 0;
	}
	
	ll pocz = 0, kon = 1000ll * 1000 * 1000 * PREC;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (czy_ujemny_cykl(-srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	cout << ((long double) pocz) / PREC;

	return 0;
}


