#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ld EPS = 0.0000000000001;
const int MAX = 200 * 1000;
ld wej[MAX + 1];
int n;

ld wartosc(ld x) {
	ld akt = wej[1] - x;
	ld maks = akt;
	for (int i = 2; i <= n; i++) {
		akt = max(akt + wej[i] - x, wej[i] - x);
		maks = max(maks, akt);
	}
	
	akt = wej[1] - x;
	ld mini = akt;
	for (int i = 2; i <= n; i++) {
		akt = min(akt + wej[i] - x, wej[i] - x);
		mini = min(mini, akt);
	}
	
	return max(abs(mini), abs(maks));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cout.precision(6);
	cout << fixed;

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	ld pocz = INT_MIN, kon = INT_MAX;
	while (abs(pocz - kon) >= EPS) {
		ld s1 = pocz + (kon - pocz) / 3;
		ld s2 = kon - (kon - pocz) / 3;
		
		ld w1 = wartosc(s1);
		ld w2 = wartosc(s2);
		
		if (w1 < w2) {
			kon = s2;
		} else {
			pocz = s1;
		}
	}
	
	cout << wartosc(pocz);

	return 0;
}

