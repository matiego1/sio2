#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int MOD = 1000 * 1000 * 1000 + 7;
para wej[MAX + 1];
int odwie[MAX + 1];

void rekur(int x, int grupa) {
	odwie[x] = grupa;
	if (odwie[wej[x].second]) return;
	rekur(wej[x].second, grupa);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> wej[i].first;
	}
	for (int i = 0; i < n; i++) {
		cin >> wej[i].second;
	}
	
	sort(wej, wej + n);
	
	int grupy = 0;
	for (int i = 0; i < n; i++) {
		if (odwie[i]) continue;
		rekur(i, ++grupy);
	}
	
	ll wynik = 1, a = 2;
	while (grupy) {
		if (grupy & 1) {
			wynik = wynik * a % MOD;
		}
		a = a * a % MOD;
		grupy /= 2;
	}
	cout << wynik;

	return 0;
}

