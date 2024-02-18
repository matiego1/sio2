#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long double ld;
typedef long long ll;

struct Punkt {
	ll x, y;
};
bool operator <(const Punkt& a, const Punkt& b) {
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
Punkt make_punkt(ll x, ll y) {
	return {x, y};
}

const ld DELTA = 0.0001;
const int MAX = 2000;
const Punkt ZERO = make_punkt(0, 0);
int n;
Punkt wej[MAX + 1];
bool odebral[MAX + 1];

ll odleg_kw(Punkt a, Punkt b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void rekur(ld R_kw, int zrodlo) {
	odebral[zrodlo] = true;
	for (int i = 1; i <= n; i++) {
		if (odebral[i]) continue;
		if (odleg_kw(wej[zrodlo], wej[i]) <= R_kw) {
			rekur(R_kw, i);
		}
	}
} 

bool sprawdz(ld R) {
	odebral[0] = true;
	for (int i = 1; i <= n; i++) {
		odebral[i] = false;
	}
	
	rekur(R * R, 0);
	
	for (int i = 1; i <= n; i++) {
		if (!odebral[i]) return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cout << fixed;
	cout.precision(6);
	
	cin >> n;
	
	wej[0] = ZERO;
	bool xi_0 = true;
	bool yi_0 = true;
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		if (a != 0) xi_0 = false;
		if (b != 0) yi_0 = false;
		wej[i] = make_punkt(a, b);
	}
	
	if (n == 1) {
		cout << sqrtl(odleg_kw(ZERO, wej[1])) << "\n";
		return 0;
	}
	
	if (n == 2) {
		ll odleg1 = odleg_kw(ZERO, wej[1]);
		ll odleg2 = odleg_kw(ZERO, wej[2]);
		ll odleg3 = odleg_kw(wej[1], wej[2]);
		
		ll wariant1 = max(odleg1, odleg2);
		ll wariant2 = max(odleg1, odleg3);
		ll wariant3 = max(odleg2, odleg3);
		
		ll wynik = min(min(wariant1, wariant2), wariant3);
		
		cout << sqrtl(wynik) << "\n";
		return 0;
	}
	if (xi_0 || yi_0) {
		sort(wej, wej + n + 1);
		
		ll maks = -1;
		for (int i = 1; i <= n; i++) {
			maks = max(maks, odleg_kw(wej[i - 1], wej[i]));
		}
		
		cout << sqrtl(maks) << "\n";
		return 0;
	}
	
	ld pocz = 0, kon = 1000ll * 1000 * 1000 * 1000;
	while (abs(kon - pocz) > DELTA) {
		ld srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + DELTA;
		}
	}
	cout << pocz << "\n";
	
	return 0;
}
