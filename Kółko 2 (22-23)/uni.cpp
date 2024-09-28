#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 20 * 1000;
int wej[MAX + 1];
int pom[MAX + 1];

void sortuj(int pocz, int kon) {
	if (pocz == kon) return;
	
	int srodek = (pocz + kon) / 2;
	sortuj(pocz, srodek);
	sortuj(srodek + 1, kon);
	
	int i = 0, i1 = pocz, i2 = srodek + 1;
	while (i1 <= srodek || i2 <= kon) {
		if (i1 > srodek) {
			pom[i++] = wej[i2++];
		} else if (i2 > kon) {
			pom[i++] = wej[i1++];
		} else {
			pom[i++] = (wej[i1] > wej[i2] ? wej[i1++] : wej[i2++]);
		}
	}
	for (int i = pocz; i <= kon; i++) {
		wej[i] = pom[i - pocz];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	if (n == 0) {
		cout << 0;
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	sortuj(1, n);
	
	int wynik = 1;
	for (int i = 2; i <= n; i++) {
		if (wej[i] != wej[i - 1]) {
			wynik++;
		}
	}
	cout << wynik;

	return 0;
}


