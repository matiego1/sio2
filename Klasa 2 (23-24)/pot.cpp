#include <iostream>
using namespace std;

const int MOD = 1000 * 1000 * 1000 + 7;

int pot(long long a, long long b) {
	long long wynik = 1;
	
	while (b > 0) {
		if (b % 2 == 1) {
			wynik = (wynik * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int q;
	cin >> q;
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << pot(a, b) << "\n";
	}

	return 0;
}