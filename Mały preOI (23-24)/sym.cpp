#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

const int MOD = 1000 * 1000 * 1000 + 7;

ll pot(ll a, ll b) {
	ll wynik = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			wynik = (wynik * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	return wynik;
}

bool warunki_brzegowe(int k, int n, int p) {
	if (k == 0 && n == 0) {
		cout << "0 0 1";
	} else if (n == 0 && p == 0) {
		cout << "1 0 0";
	} else if (k == 0 && p == 0) {
		cout << "0 1 0";
	} else if (k == 0) {
		cout << "0 1 0";
	} else if (n == 0) {
		cout << "0 0 1";
	} else if (p == 0) {
		cout << "1 0 0";
	} else {
		return false;
	}
	return true;
}

const int MAX = 200;
ll dp[MAX + 1][MAX + 1][MAX + 1];
ll odwrotnosci[3 * MAX * MAX + 1];

ll pomnoz4(ll a, ll b, ll c, ll d) {
	return (((((a * b) % MOD) * c) % MOD) * d) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int k, n, p;
	cin >> k >> n >> p;
	
	for (int i = 1; i <= 3 * MAX * MAX; i++) {
		odwrotnosci[i] = pot(i, MOD - 2);
	}
	
	if (warunki_brzegowe(k, n, p)) {
		return 0;
	}
	
	dp[k][n][p] = 1;
	for (int i = k; i >= 0; i--) {
		for (int j = n; j >= 0; j--) {
			for (int l = p; l >= 0; l--) {
				ll kombinacje = i * j + i * l + j * l;
				if (kombinacje == 0) continue;
				kombinacje = odwrotnosci[kombinacje];
				
				if (i > 0) dp[i - 1][j][l] = (dp[i - 1][j][l] + pomnoz4(dp[i][j][l], i, l, kombinacje)) % MOD;
				if (j > 0) dp[i][j - 1][l] = (dp[i][j - 1][l] + pomnoz4(dp[i][j][l], i, j, kombinacje)) % MOD;
				if (l > 0) dp[i][j][l - 1] = (dp[i][j][l - 1] + pomnoz4(dp[i][j][l], l, j, kombinacje)) % MOD;
			}
		}
	}
	
	ll wynik_k = 0, wynik_n = 0, wynik_p = 0;
	for (int i = 1; i <= k; i++) {
		wynik_k = (wynik_k + dp[i][0][0]) % MOD;
	}
	for (int i = 1; i <= n; i++) {
		wynik_n = (wynik_n + dp[0][i][0]) % MOD;
	}
	for (int i = 1; i <= p; i++) {
		wynik_p = (wynik_p + dp[0][0][i]) % MOD;
	}
	
	cout << wynik_k << " " << wynik_n << " " << wynik_p << "\n";
	
	return 0;
}
