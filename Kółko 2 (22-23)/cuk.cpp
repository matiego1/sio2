#include <iostream>
using namespace std;

const int MAX = 1000;
int DP[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	
	for (int i = 0; i < n; i++) {
		int c, s;
		cin >> c >> s;
		for (int j = k; j >= 0; j--) {
			if (j + c <= k) {
				DP[j + c] = max(DP[j + c], DP[j] + s);
			}
		}
	}
	
	cout << DP[k];
	
	return 0;
}
