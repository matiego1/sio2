#include <iostream>
using namespace std;
typedef long long ll;

const int MAX = 500 * 1000;
char s[2 * MAX + 15];
int dp[2 * MAX + 15];

char odwroc(char c) {
	if (c == '0') return '1';
	if (c == '1') return '0';
	return c;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	string wej;
	cin >> wej;
	
	s[0] = 'P';
	s[1] = '#';
	for (int i = 0; i < n; i++) {
		s[2 * i + 2] = wej[i];
		s[2 * i + 3] = '#';
	}
	s[2 * n + 2] = 'K';
	
	n = 2 * n + 1;
	
	ll wynik = 0;
	int pocz = 1, kon = 1;
	for (int i = 1; i <= n; i++) {
		dp[i] = max(0, min(kon - i, dp[pocz + kon - i]));
		
		while (odwroc(s[i - dp[i]]) == s[i + dp[i]]) {
			dp[i]++;
		}
		
		if (i + dp[i] > kon) {
			pocz = i - dp[i];
			kon = i + dp[i];
		}
		
		if (s[i] == '#') {
			wynik += dp[i] - 1;
		}
	}
	cout << wynik / 2;
	
	return 0;
}
