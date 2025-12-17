#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> para;

const ld PI = acosl(-1.0L);
const ld EPS = 0.00000000001L;
const int MAX = 50 * 1000;
para wej[MAX + 1];
ld poczatki[MAX + 1];

ld normalizuj(ld x) {
	x = fmodl(x, PI * 2);
	if (x < 0) x += PI * 2;
	return x;
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	ld R;
	cin >> n >> R;
	
	for (int i = 1; i <= n; i++) {
		ll x, y;
		cin >> x >> y;
		
		ld alfa = atan2l(y, x);
		ld d = sqrtl(x * x + y * y);
		ld beta = acosl(R / d);
		
		ld pocz = normalizuj(alfa - beta);
		ld kon = normalizuj(alfa + beta);		
		
		wej[i] = {pocz, kon};
		poczatki[i] = pocz;
	}
	
	sort(poczatki + 1, poczatki + 1 + n);
	
	ll wynik = 0;
	for (int i = 1; i <= n; i++) {
		ld pocz = wej[i].first - EPS, kon = wej[i].second + EPS;
		
		if (pocz <= kon) {
			auto lewy = lower_bound(poczatki + 1, poczatki + 1 + n, pocz);
			auto prawy = upper_bound(poczatki + 1, poczatki + 1 + n, kon);
			wynik += prawy - lewy;
		} else {
			auto prawy = lower_bound(poczatki + 1, poczatki + 1 + n, pocz);
			wynik += poczatki + 1 + n - prawy;
			
			auto lewy = upper_bound(poczatki + 1, poczatki + 1 + n, kon);
			wynik += lewy - (poczatki + 1);
		}
	}
	cout << wynik - n;

	return 0;
}
