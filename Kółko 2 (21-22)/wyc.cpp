#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;

int wej[MAX];
int n, k;

bool sprawdz(ll odleglosc) {
	ll dni = 0, pozostale = 0;
	
	for (int i = 1; i < n; i++) {
		if (wej[i] > odleglosc) return false;
		if (wej[i] > pozostale) {
			pozostale = odleglosc - wej[i];
			dni++;
		} else {
			pozostale -= wej[i];
		}
	}
	
	return (dni <= k);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	
	for (int i = 1; i < n; i++) {
		cin >> wej[i];
	}
	
	ll pocz = 1, kon = 1000ll * 1000 * 1000 * 1000;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	cout << pocz;

	return 0;
}


