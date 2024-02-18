#include <iostream>
using namespace std;
typedef pair<int, int> para;
typedef long double ld;

const int MAX = 100 * 1000;
const ld EPS = 0.000001;
para wej[MAX + 1];

ld policz(int n, ld predkosc) {
	ld wynik = 0;
	for (int i = 1; i <= n; i++) {
		wynik += wej[i].first / (wej[i].second + predkosc);
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cout.precision(5);
	cout << fixed;
	
	int n, t;
	cin >> n >> t;
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		wej[i] = {a, b};
	}
	
	ld pocz = EPS, kon = 50 * 1000;
	while (abs(kon - pocz) >= EPS) {
		ld srodek = (pocz + kon) / 2;
		if (policz(n, srodek) >= t) {
			pocz = srodek;
		} else {
			kon = srodek - EPS;
		}
	}
	cout << pocz;

	return 0;
}

