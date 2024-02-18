#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll n;
	cin >> n;
	
	ld pierwiastek = sqrtl(n);
	if (abs((ll) pierwiastek - pierwiastek) <= 0.000001) {
		cout << (ll) pierwiastek + 1;
	} else {
		cout << (ll) ceill(pierwiastek);
	}

	return 0;
}

