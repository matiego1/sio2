#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_M = 8;
int wej[MAX_M + 1];
ll wart[1 << MAX_M];
ll dp[2];
ll pop[1 << MAX_M];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	const int pelna = (1 << m) - 1;
	
	for (int maska = 0; maska < (1 << m); maska++) {
		pop[maska] = LLONG_MIN;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> wej[j];
		}
		
		for (int maska = 0; maska < (1 << m); maska++) {
			wart[maska] = 0;
			for (int j = 1; j <= m; j++) {
				if (maska & (1 << (j - 1))) {
					wart[maska] += wej[j];
				} else {
					wart[maska] -= wej[j]; 
				}
			}
		}
		
		dp[i % 2] = dp[(i - 1) % 2];
		for (int maska = 0; maska < (1 << m); maska++) {
			if (pop[pelna ^ maska] > LLONG_MIN) {
				dp[i % 2] = max(dp[i % 2], wart[maska] + pop[pelna ^ maska]);
			}
		}
		
		for (int maska = 0; maska < (1 << m); maska++) {
			pop[maska] = max(pop[maska], dp[(i - 1) % 2] + wart[maska]);
		}
	}
	
	cout << dp[n % 2];

	return 0;
}

