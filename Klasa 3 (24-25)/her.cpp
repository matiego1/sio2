#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int R = (1 << 18);
ll tree[2 * R];
ll suma[2 * R];

void ustaw(int i, int wart) {
	i += R;
	
	tree[i] = 0;
	suma[i] = wart;
	
	while (i > 1) {
		i /= 2;
		tree[i] = tree[2 * i] + tree[2 * i + 1] + 2 * suma[2 * i] * suma[2 * i + 1];
		suma[i] = suma[2 * i] + suma[2 * i + 1];
	}
}

ll query(int pocz, int kon) {
	pocz += R;
	kon += R;
	
	ll wynik = 0, s = suma[pocz];
	if (pocz != kon) {
		wynik = 2 * s * suma[kon];
		s += suma[kon];
	}
	
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik += tree[pocz + 1] + 2 * s * suma[pocz + 1];
			s += suma[pocz + 1];
		}
		if (kon % 2 == 1) {
			wynik += tree[kon - 1] + 2 * s * suma[kon - 1];
			s += suma[kon - 1];
		}
		pocz /= 2;
		kon /= 2;
	}
	
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> suma[i + R];
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = tree[2 * i] + tree[2 * i + 1] + 2 * suma[2 * i] * suma[2 * i + 1];
		suma[i] = suma[2 * i] + suma[2 * i + 1];
	}
	
	while (m--) {
		int typ, a, b;
		cin >> typ >> a >> b;
		
		if (typ == 0) {
			ustaw(a, b);
		} else {
			cout << query(a, b) / 2 << "\n";
		}
	}

	return 0;
}
