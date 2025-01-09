#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int INF = INT_MAX;
const int MAX_N = 3;
const int MAX_M = 1000 * 1000;
int wej[MAX_M + 1][MAX_N + 1];
int dp[1 << MAX_N][MAX_M + 1];

int f(int x) {
	return (x ? 1 : 0);
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	if (n == 1) {
		cout << 0;
		return 0;
	}
	if (n > 3) {
		cout << -1;
		return 0;
	}
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			char c;
			cin >> c;
			wej[x][y] = (c - '0');
		}
	}
	
	if (n == 2) {
		for (int i = 1; i <= m; i++) {
			for (int maska = 0; maska < 4; maska++) {
				int gora = f(maska & 1);
				int dol = f(maska & 2);
				
				int koszt_zmiany = (wej[i][1] != gora) + (wej[i][2] != dol);
				
				dp[maska][i] = min(dp[maska ^ 1][i - 1], dp[maska ^ 2][i - 1]) + koszt_zmiany;
			}
		}
	} else {
		for (int i = 1; i <= m; i++) {
			for (int maska = 0; maska < 8; maska++) {
				int gora = f(maska & 1);
				int srodek = f(maska & 2);
				int dol = f(maska & 4);
				
				int pop0 = ((1 ^ srodek ^ dol) << 2) | (1 ^ gora ^ srodek);
				int pop1 = ((srodek ^ dol) << 2) | 2 | (gora ^ srodek);
				int koszt_zmiany = (wej[i][1] != gora) + (wej[i][2] != srodek) + (wej[i][3] != dol);
				
				dp[maska][i] = min(dp[pop0][i - 1], dp[pop1][i - 1]) + koszt_zmiany;
			}
		}
	}
		
	int wynik = dp[0][m];
	for (int maska = 1; maska < (1 << n); maska++) {
		wynik = min(wynik, dp[maska][m]);
	}
	cout << wynik;

	return 0;
}

