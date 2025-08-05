#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int R = (1 << 17);
int wej[MAX + 1];
ll mini[2 * R];
ll maks[2 * R];

ll query_maks(int pocz, int kon) {
	pocz += R - 1;
	kon += R + 1;
	ll wynik = maks[pocz + 1];
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik = max(wynik, maks[pocz + 1]);
		}
		if (kon % 2 == 1) {
			wynik = max(wynik, maks[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	return wynik;
}
ll query_mini(int pocz, int kon) {
	pocz += R - 1;
	kon += R + 1;
	ll wynik = mini[pocz + 1];
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik = min(wynik, mini[pocz + 1]);
		}
		if (kon % 2 == 1) {
			wynik = min(wynik, mini[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		wej[i] = a - wej[i];
		mini[R + i] = mini[R + i - 1] + wej[i];
		maks[R + i] = maks[R + i - 1] + wej[i];
	}
	
	for (int i = R - 1; i >= 1; i--) {
		mini[i] = min(mini[2 * i], mini[2 * i + 1]);
		maks[i] = max(maks[2 * i], maks[2 * i + 1]);
	}
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		
		if (maks[R + r] - maks[R + l - 1] != 0) {
			cout << "-1\n";
			continue;
		}
		
		ll m = query_mini(l, r) - mini[R + l - 1];
		if (m < 0) {
			cout << "-1\n";
			continue;
		}
		
		cout << max(query_maks(l, r) - maks[R + l - 1], m) << "\n";
	}

	return 0;
}

