#include <iostream>
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll n, m;
	cin >> n >> m;
	
	ll wynik = n * (n + 1) / 2, akt = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		if (a < m) {
			akt++;
		} else {
			wynik -= akt * (akt + 1) / 2;
			akt = 0;
		}
	}
	wynik -= akt * (akt + 1) / 2;
	cout << wynik;

	return 0;
}

