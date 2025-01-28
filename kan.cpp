#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
int x[MAX + 1];
int a[MAX + 1];
int b[MAX + 1];
int n;

ld wart(ld ileA) {
	ld ileB = INT_MAX;
	for (int i = 1; i <= n; i++) {
		if (ileA * a[i] > x[i]) return 0;
		ileB = min(ileB, ((ld) x[i] - ileA * a[i]) / (ld) b[i]);
	}
	return ileA + ileB;
}

int wart_dokl(int ileA) {
	int ileB = INT_MAX;
	for (int i = 1; i <= n; i++) {
		if (ileA * a[i] > x[i]) return 0;
		ileB = min(ileB, (x[i] - ileA * a[i]) / b[i]);
	}
	return ileA + ileB;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	
	int maksA = INT_MAX;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		maksA = min(maksA, x[i] / a[i]);
	}
	
	int maksB = INT_MAX;
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		maksB = min(maksB, x[i] / b[i]);
	}
	
	ld pocz = 0, kon = maksA;
	while (abs(kon - pocz) >= 3) {
		ld s1 = pocz + (kon - pocz + 1) / 3;
		ld s2 = kon - (kon - pocz + 1) / 3;
		ld w1 = wart(s1);
		ld w2 = wart(s2);
		
		if (w1 <= w2) {
			pocz = s1;
		} else {
			kon = s2;
		}
	}
	
	int wynik = max(maksA, maksB);
	for (int i = max(0, (int) floor(pocz) - 5); i <= min(maksA, (int) ceil(kon) + 5); i++) {
		wynik = max(wynik, wart_dokl(i));
	}
	cout << wynik;

	return 0;
}
