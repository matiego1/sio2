#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

const int MAX = 100 * 1000;
const ld EPS = 0.01;

int n, k;
int wej[MAX + 1];

bool sprawdz(ld zasieg) {
	ld koniec = wej[1] + zasieg + zasieg;
	int wykorzystane = 1;
	
	for (int i = 2; i <= n; i++) {
		if (wej[i] > koniec) {
			wykorzystane++;
			koniec = wej[i] + zasieg + zasieg;
		}
	}
	
	return (wykorzystane <= k);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cout.precision(1);
	cout << fixed;

	cin >> k >> n;
	
	if (k >= n) {
		cout << 0.0;
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	sort(wej + 1, wej + 1 + n);
	
	ld pocz = 0, kon = 1000 * 1000;
	while (abs(pocz - kon) >= EPS) {
		ld srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + EPS;
		}
	}
	cout << pocz;

	return 0;
}

