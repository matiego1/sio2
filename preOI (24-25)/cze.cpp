#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_N = 400;
const int MAX_X = 200 * 1000;
int pref[MAX_N + 1];
ll dp[MAX_X + 1];
ll wynik[MAX_N + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int x_ory;
	cin >> x_ory;
	int x = x_ory;
	
	string s;
	cin >> s;
	int n = (int) s.length();
	s = "$" + s;
	
	for (int i = 1; i <= n; i++) {
		pref[i] = pref[i - 1] + (s[i] == 'N');
	}
	
	int maks = 1;
	for (int i = 2; i <= n; i++) {
		if (pref[i] * maks > pref[maks] * i) {
			maks = i;
		}
	}
	
	ll W = 0;
	while (x >= MAX_X) {
		W += pref[maks];
		wynik[maks]++;
		x -= maks;
	}
	
	for (int i = 1; i <= x; i++) dp[i] = INT_MIN;
	
	for (int i = 1; i <= min(n, x); i++) {
		for (int j = i; j <= x; j++) {
			if (dp[j - i] != INT_MIN) {
				dp[j] = max(dp[j], dp[j - i] + pref[i]);
			}
		}
	}
	
	cout << x_ory - (dp[x] + W) << "\n";
	
	while (x > 0) {
		for (int i = 1; i <= n; i++) {
			if (x >= i && dp[x] == dp[x - i] + pref[i]) {
				wynik[i]++;
				x -= i;
				break;
			}
		}
	}
	
	for (int i = n; i >= 1; i--) {
		wynik[i] += wynik[i + 1];
	}
	
	for (int i = 1; i <= n; i++) {
		cout << wynik[i] << " ";
	}

	return 0;
}

