#include <iostream>
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int k;
	cin >> k;
	
	ll wynik = 1;
	for (int i = 0; i <= k; i++) {
		int a;
		cin >> a;
		
		int wart = (1 << i);
		
		for (int j = 1; j <= a; j++) {
			if (wart > wynik) {
				cout << wynik;
				return 0;
			}
			wynik += wart;
		}
	}
	cout << wynik;

	return 0;
}

