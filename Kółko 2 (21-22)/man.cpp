#include <iostream>
using namespace std;
typedef long long ll;

const int MAX = 100 * 1000;
char s[2 * MAX + 15];
int dp[2 * MAX + 15];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	string wej;
	cin >> wej;

	s[0] = 'P';
	s[1] = '#';
	for (int i = 0; i < n; i++) {
		s[2 * i + 2] = wej[i];
		s[2 * i + 3] = '#';
	}
	s[2 * n + 2] = 'K';

	n = 2 * n + 1;

	int pocz = 1, kon = 1;
	for (int i = 1; i <= n; i++) {
		dp[i] = max(0, min(kon - i, dp[pocz + kon - i]));

		while (s[i - dp[i]] == s[i + dp[i]]) {
			dp[i]++;
		}

		if (i + dp[i] > kon) {
			pocz = i - dp[i];
			kon = i + dp[i];
		}
	}


	for (int i = 2; i <= n; i += 2) {
        cout << dp[i] / 2 << " ";
	}
	cout << "\n";

    for (int i = 3; i < n; i += 2) {
        cout << (dp[i] - 1) / 2 << " ";
	}
	cout << "\n";

	return 0;
}
