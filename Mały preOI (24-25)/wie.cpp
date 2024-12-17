#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
int A[MAX + 1];
int B[MAX + 1];
int schematy[MAX + 1];
int dp[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> B[i];
	}

	for (int i = 0; i <= MAX; i++) schematy[i] = INT_MAX;
	for (int i = 1; i <= n; i++) {
		schematy[A[i]] = min(schematy[A[i]], A[i] - B[i]);
	}
	for (int i = 1; i <= MAX; i++) {
		schematy[i] = min(schematy[i], schematy[i - 1]);
	}
	
	for (int i = 1; i <= MAX; i++) {
		if (schematy[i] != INT_MAX) {
			dp[i] = dp[max(0, i - schematy[i])] + 2;
		}
	}
	
	ll wynik = 0;
	for (int i = 1; i <= m; i++) {
		int masa;
		cin >> masa;
		
		while (masa > MAX) {
			int ile = (masa - MAX - 1) / schematy[MAX] + 1;
			masa -= ile * schematy[MAX];
			wynik += 2 * ile;
		}
		wynik += dp[masa];
	}
	cout << wynik;
	
	return 0;
}


