#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
int wej[MAX + 1];

int policz(int mini, int maks) {
	int srodek = (mini + maks) / 2;
	return max(maks - srodek, srodek - mini);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, t;
	cin >> n >> t;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		wej[i] %= t;
	}
	
	sort(wej + 1, wej + 1 + n);
	
	int wynik = policz(wej[1], wej[n]);
	for (int i = 1; i < n; i++) {
		wynik = min(wynik, policz(wej[i + 1] - t, wej[i]));
	}
	cout << wynik;

	return 0;
}

