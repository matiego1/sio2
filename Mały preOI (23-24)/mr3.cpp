#include <iostream>
using namespace std;
typedef long long ll;

const int MAX = 2 * 100 * 1000;
int n, k;
int wej[MAX + 1];

bool sprawdz(ll x) {
	int indeks = n;
	while (wej[indeks] > x) {
		indeks--;
	}
	
	for (int i = 1; i <= k; i++) {
		x -= indeks;
		while (indeks > 1 && wej[indeks] > x) {
			indeks--;
		}
	}
	
	return x >= 1;
}

ll rozwiaz() {
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	if (wej[1] != 1) {
		return 1;
	}
	
	ll pocz = 1, kon = 1000000000000000000ll; // 10 ** 18;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	
	return pocz;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		cout << rozwiaz() << "\n";
	}

	return 0;
}

