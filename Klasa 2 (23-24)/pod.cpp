#include <iostream>
#include <map>
using namespace std;

const int MAX = 5 * 100 * 1000;
const int MOD = 1000 * 1000 * 1000 + 7;
int wej[MAX + 1];
int dp[MAX + 1];
map<int, int> ost;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	dp[0] = 1;
	
	for (int i = 1; i <= n; i++) {
		dp[i] = (2 * dp[i - 1]) % MOD;
		
		if (ost[wej[i]] != 0) {
			dp[i] = (dp[i] - dp[ost[wej[i]] - 1] + MOD) % MOD;
		}
		
		ost[wej[i]] = i;
	}
	
	cout << dp[n];
	
	return 0;
}

