#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
int wej[MAX + 1];
int n, k;

bool sprawdz(ll srodek) {
	int czesci = 0;
	ll suma = 0;
	for (int i = 1; i <= n; i++) {
		if (suma + wej[i] > srodek) {
			czesci++;
			suma = 0;
		}
		if (suma + wej[i] > srodek) return false;
		suma += wej[i];
	}
	if (suma > 0) czesci++;
	return (czesci <= k);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	ll pocz = 0, kon = 1000ll * 1000 * 1000 * 1000 * 1000;
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

