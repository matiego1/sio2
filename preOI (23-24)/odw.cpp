#include <iostream>
using namespace std;

const int MAX = 5000;
int dp[MAX][MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	string a, b;
	cin >> a >> b;
	
	int zgodnosc = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == b[i]) zgodnosc++;
	}
	
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (i >= j) {
				dp[i][j] = zgodnosc;
			} else {
				dp[i][j] = dp[i + 1][j - 1] - (a[i] == b[i]) - (a[j] == b[j]) + (a[i] == b[j]) + (a[j] == b[i]);
			}
		}
	}

	int maks = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			maks = max(maks, dp[i][j]);
		}
	}
	cout << maks;
	
	return 0;
}

