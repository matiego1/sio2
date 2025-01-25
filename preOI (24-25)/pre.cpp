#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int R = (1 << 20);
ll tree[2 * R];

ll query(int pocz, int kon) {
	pocz += R;
	kon += R;
	
	ll wynik = max(tree[pocz], tree[kon]);
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik = max(wynik, tree[pocz + 1]);
		}
		if (kon % 2 == 1) {
			wynik = max(wynik, tree[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int d, p;
	cin >> d >> p;
	
	for (int i = 1; i <= d; i++) {
		int trudnosc, zysk;
		cin >> trudnosc >> zysk;
		
		tree[R + trudnosc] = max(tree[R + trudnosc], (ll) zysk);
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = max(tree[2 * i], tree[2 * i + 1]);
	}
	
	ll wynik = 0;
	
	for (int i = 1; i <= p; i++) {
		int trudnosc, strata;
		cin >> trudnosc >> strata;
		
		ll zysk = query(0, trudnosc) - strata;
		wynik += max(0ll, zysk);
	}
	
	cout << wynik;
	
	return 0;
}

