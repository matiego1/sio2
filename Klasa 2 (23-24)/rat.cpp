#include <iostream>
using namespace std;

int odleg_kw(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k, x, y;
	cin >> n >> k >> x >> y;
	
	int wynik = 0;
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		
		if (odleg_kw(x, y, a, b) <= k * k) {
			wynik++;
		}
	}
	
	cout << n - wynik;

	return 0;
}

