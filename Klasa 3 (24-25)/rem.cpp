#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 5000;
int wej[MAX + 1];
ll pref[MAX + 1];
ll dp[MAX + 2][MAX + 1];

ll suma_pref(int lewy, int prawy) {
	return pref[prawy] - pref[lewy - 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		pref[i] = pref[i - 1] + wej[i];
	}
	
	for (int lewy = n; lewy >= 1; lewy--) {
		for (int prawy = lewy; prawy <= n; prawy++) {
			if (lewy == prawy) {
				dp[lewy][prawy] = wej[lewy];
			} else {
				dp[lewy][prawy] = max(wej[lewy] + suma_pref(lewy + 1, prawy) - dp[lewy + 1][prawy], wej[prawy] + suma_pref(lewy, prawy - 1) - dp[lewy][prawy - 1]);
			}
		}
	}

	cout << dp[1][n];

	return 0;
}


