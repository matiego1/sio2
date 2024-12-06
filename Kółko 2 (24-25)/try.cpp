#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int MAX = 1000 * 1000;
const ll INF = LLONG_MAX;
para przedzialy[MAX + 1];
ll wynik[MAX + 1];
int n;

bool sprawdz(ll odstep) {
	ll nast = -INF;
	for (int i = 1; i <= n; i++) {
		if (nast > przedzialy[i].second) return false;
		nast = max(przedzialy[i].first, nast);
		wynik[i] = nast;
		nast += odstep;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> przedzialy[i].first >> przedzialy[i].second;
	}
	
	if (!sprawdz(1)) {
		cout << "NIE";
		return 0;
	}
	
	ll pocz = 0, kon = 10ll * 1000 * 1000 * 1000;
	while (pocz < kon) {
		ll srodek = (pocz + kon + 1) / 2;
		if (sprawdz(srodek)) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
		}
	}
	cout << pocz << "\n";
	
	sprawdz(pocz);
	for (int i = 1; i <= n; i++) {
		cout << wynik[i] << " ";
	}

	return 0;
}

