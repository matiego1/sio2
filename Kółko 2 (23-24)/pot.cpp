#include <iostream>
using namespace std;
typedef long long ll;

const int MOD = 1000 * 1000 * 1000 + 7;

void rozwiaz() {
	ll a, b;
	cin >> a >> b;
	
	ll wynik = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			wynik = (wynik * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	
	cout << wynik << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		rozwiaz();
	}
	
	return 0;
}
