#include <iostream>
using namespace std;
typedef long double ld;

const ld EPS = 0.0001;
const int MAX = 1000 * 1000;
int wej[MAX + 1];
int n;

bool sprawdz(ld x) {
	ld pop = wej[1] - x;
	for (int i = 2; i <= n; i++) {
		if (pop > wej[i] + x) return false;
		pop = max(pop, wej[i] - x);
	}
    return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cout.precision(3);
	cout << fixed;
	
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	ld pocz = 0, kon = 1000 * 1000 * 1000;
	while (abs(pocz - kon) >= EPS) {
		ld srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek;
		}
	}
	
	cout << pocz << "\n";
	
	ld pop = wej[1] - pocz;
	cout << pop << "\n";
	for (int i = 2; i <= n; i++) {
		pop = max(pop, wej[i] - pocz);
		cout << pop << "\n";
	}
	
	return 0;
}

