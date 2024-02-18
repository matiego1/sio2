#include <iostream>
#include <vector>
using namespace std;

const int MAX = 30 * 1000 + 1; //+1, bo zero te� mo�e by�
int dp[MAX + 1];
vector<int> wyklady[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		wyklady[b].push_back(a);
	}
	
	for (int i = 1; i <= MAX; i++) {
		dp[i] = dp[i - 1];
		for (int j = 0; j < wyklady[i].size(); j++) {
			int pocz = wyklady[i][j];
			dp[i] = max(dp[i], dp[pocz] + i - pocz);
		}
	}
	
	cout << dp[MAX];

	return 0;
}