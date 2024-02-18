#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

struct Krawedz {
	int v, u, waga;
};

const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int PREC = 1000;
const int MAX_N = 100;
const int MAX_M = 10 * 1000;
int n, m;
Krawedz krawedzie[MAX_M + 1];
ll odleg[MAX_N + 1][MAX_N + 1];

bool czy_ujemny_cykl(ll x) { // czy jest ujemny cykl, jak do wszystkich krawedzi dodamy x
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			odleg[i][j] = INF;
		}
	}
	
	for (int i = 1; i <= m; i++) {
		odleg[krawedzie[i].v][krawedzie[i].u] = krawedzie[i].waga + x;
	}
	for (int i = 1; i <= n; i++) {
		odleg[i][i] = 0;
	}
	
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
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
	
	cout << fixed;
	cout.precision(3);
	
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, -c * PREC};
	}
	
	if (!czy_ujemny_cykl(0)) {
		// w grafie istnieja tylko cykle ujemne, albo wogole ich nie ma
		ll pocz = 0, kon = 100ll * 100 * 1000 * PREC;
		while (pocz < kon) {
			ll srodek = (pocz + kon) / 2;
			if (czy_ujemny_cykl(-srodek)) {
				kon = srodek;
			} else {
				pocz = srodek + 1;
			}
		}
		cout << -((long double) pocz) / PREC;
		return 0;
	}
	
	ll pocz = 1, kon = 100ll * 100 * 1000 * PREC;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (czy_ujemny_cykl(srodek)) {
			pocz = srodek + 1;
		} else {
			kon = srodek;
		}
	}
	
	cout << ((long double) pocz) / PREC;

	return 0;
}