#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = (1 << 20);
para dp[2 * MAX + 10];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 2 * MAX + 10; i++) dp[i] = {INT_MAX, -1};
	
	int n, k, q;
	cin >> n >> k >> q;
	
	for (int i = 1; i <= n; i++) {
		int koszt, ile, suknia = 0;
		cin >> koszt >> ile;
		for (int j = 1; j <= ile; j++) {
			int a;
			cin >> a;
			suknia |= (1 << (a - 1));
		}
		if (koszt < dp[suknia].first) {
			dp[suknia] = {koszt, i};
		}
	}
	
	for (int i = MAX; i >= 0; i--) {
		for (int j = 0; j < 20; j++) {
			dp[i] = min(dp[i], dp[i | (1 << j)]);
		}
	}
	
	for (int i = 1; i <= q; i++) {
		int ile, suknia = 0;
		cin >> ile;
		for (int j = 1; j <= ile; j++) {
			int a;
			cin >> a;
			suknia |= (1 << (a - 1));
		}
		if (dp[suknia].second == -1) {
			cout << "NIE\n";
		} else {
			cout << dp[suknia].second << "\n";
		}
	}

	return 0;
}

