#include <iostream>
using namespace std;

const int MAX = 1000;
int wej[MAX + 1][MAX + 1];
int dp[MAX + 1][MAX + 1];
int n;

bool sprawdz(int mediana) {
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]) + (wej[x][y] >= mediana);
		}
	}
	return dp[n][n] >= n;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> wej[x][y];
		}
	}
	
	int pocz = 1, kon = 1000 * 1000 * 1000;
	while (pocz < kon) {
		int srodek = (pocz + kon + 1) / 2;
		if (sprawdz(srodek)) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
		}
	}
	cout << pocz;

	return 0;
}

