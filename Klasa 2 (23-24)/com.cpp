#include <iostream>
using namespace std;

const int MAX = 5000;
int DP[MAX + 1][MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string a, b;
	cin >> a >> b;

	for (int i = 1; i <= a.length(); i++) {
		for (int j = 1; j <= b.length(); j++) {
			if (a[i - 1] == b[j - 1]) {
				DP[i][j] = DP[i - 1][j - 1] + 1;
			} else {
				DP[i][j] = max(DP[i - 1][j] , DP[i][j - 1]);
			}
		}
	}

	cout << DP[a.length()][b.length()] << "\n";

	if (DP[a.length()][b.length()] == 0) {
		return 0;
	}

	string wynik;

	int x = a.length(), y = b.length();
	while (x >= 1 && y >= 1) {
		if (DP[x][y] == DP[x - 1][y]) {
			x--;
		} else if (DP[x][y] == DP[x][y - 1]) {
			y--;
		} else if (DP[x][y] == DP[x - 1][y - 1] + 1) {
			wynik += a[x - 1];
			x--;
			y--;
		}
	}

	for (int i = wynik.length() - 1; i >= 0; i--) {
		cout << wynik[i];
	}

	return 0;
}
