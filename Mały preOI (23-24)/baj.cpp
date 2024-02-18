#include <iostream>
using namespace std;
typedef long long ll;

const int MOD = 1000 * 1000 * 1000 + 7;

ll pot(ll a, ll b) {
	ll wynik = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			wynik = (wynik * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	return wynik;
}

ll pot_bez_mod(ll a, ll b) {
	ll wynik = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			wynik *= a;
		}
		a *= a;
		b /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int k, n;
	cin >> k >> n;
	
	if (n == 0) {
		cout << (6 * pot(4, pot_bez_mod(2, k) - 2)) % MOD;
	}

	return 0;
}

