#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
int wej[MAX + 1];

int maks(int pocz, int kon) {
	if (pocz == kon) return wej[pocz];
	int lewy = maks(pocz, (pocz + kon) / 2);
	int prawy = maks((pocz + kon) / 2 + 1, kon);
	return (lewy > prawy ? lewy : prawy);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	cout << maks(1, n);

	return 0;
}


