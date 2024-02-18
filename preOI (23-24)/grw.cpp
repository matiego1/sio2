#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

const int MOD = 1000 * 1000 * 1000 + 7;
const int MAX = 500;
char wej[MAX + 1][MAX + 1];
int dp[4 * MAX][4 * MAX]; // wystarczy?
int pref[4 * MAX][4 * MAX]; // wystarczy?

int X(int x, int y) {
	return x - y + MAX;
}
int Y(int x, int y) {
	return x + y;
}

int suma_pref(int x1, int y1, int x2, int y2) {
	ll wynik = pref[x2][y2];
	wynik = (wynik - pref[x1 - 1][y2] + MOD) % MOD;
	wynik = (wynik - pref[x2][y1 - 1] + MOD) % MOD;
	wynik = (wynik + pref[x1 - 1][y1 - 1]) % MOD;
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k, j;
	cin >> n >> m >> k >> j;
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			cin >> wej[x][y];
			if (wej[x][y] == 'S') {
				dp[X(x, y)][Y(x, y)] = 1;
			}
		}
	}
	
	for (int i = 1; i <= k; i++) {
		for (int y = Y(1, 1); y <= Y(m, n); y++) {
			for (int x = X(1, n); x <= X(m, 1); x++) {
				ll akt = (pref[x - 1][y] + pref[x][y - 1]) % MOD;
				akt = (akt - pref[x - 1][y - 1] + MOD) % MOD;
				akt = (akt + dp[x][y]) % MOD;;
				pref[x][y] = akt;
			}
		}
		for (int y = 1; y <= n; y++) {
			for (int x = 1; x <= m; x++) {
				if (wej[x][y] == 'B' || wej[x][y] == 'S') {
					int x1 = X(x, y), y1 = Y(x, y);
					dp[x1][y1] = suma_pref(max(1, x1 - j), max(1, y1 - j), min(X(m, 1), x1 + j), min(Y(m, n), y1 + j));
				}
			}
		}
	}
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			if (wej[x][y] == 'B' || wej[x][y] == 'S') {
				cout << dp[X(x, y)][Y(x, y)] << " ";
			} else {
				cout << -1 << " ";
			}
		}
		cout << "\n";
	}

	return 0;
}

