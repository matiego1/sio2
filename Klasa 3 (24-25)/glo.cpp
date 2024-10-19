#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 200 * 1000;
int wej[MAX + 1];
int dp1[MAX + 1];
int dp2[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, x;
	cin >> n >> x;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	dp1[0] = -INF;
	dp2[0] = -INF;
	for (int i = 1; i <= n; i++) {
		dp1[i] = INF;
		dp2[i] = INF;
	}
	
	for (int i = 1; i <= n; i++) {
		
		int indeks1 = lower_bound(dp1 + 1, dp1 + 1 + n, wej[i]) - dp1;
		dp1[indeks1] = wej[i];
		
		int indeks2 = lower_bound(dp2 + 1, dp2 + 1 + n, wej[i]) - dp2;
		dp2[indeks2] = wej[i];
		
		dp2[indeks1] = min(dp2[indeks1], wej[i] - x);
	}
	
	for (int i = n; i >= 1; i--) {
		if (dp2[i] != INF) {
			cout << i;
			return 0;
		}
	}

	return 0;
}


