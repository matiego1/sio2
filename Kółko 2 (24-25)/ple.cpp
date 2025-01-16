#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100;
const int MAX_B = 10 * 1000;
int masa[MAX_N + 1];
int wart[MAX_N + 1];
int dp[MAX_N + 1][MAX_B + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, B;
	cin >> n >> B;
	
	for (int i = 1; i <= n; i++) {
		cin >> masa[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> wart[i];
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= B; j++) {
			if (masa[i] <= j) {
				dp[i][j] = max(dp[i - 1][j - masa[i]] + wart[i], dp[i - 1][j]);
			} else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	
	cout << dp[n][B] << "\n";
	
	vector<int> wybrane;
	for (int i = n; i > 0 && B > 0; i--) {
		if (dp[i][B] != dp[i - 1][B]) {
			wybrane.push_back(i);
			B -= masa[i];
		}
	}
	
	cout << wybrane.size() << "\n";
	
	for (int i : wybrane) {
		cout << i << " ";
	}

	return 0;
}