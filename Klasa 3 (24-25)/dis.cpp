#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
 
const int MOD = 1000 * 1000 * 1000 + 7;
 
ll potega(ll a, int b) {
	ll wynik = 1;
	while (b > 0) {
		if (b & 1) {
			wynik = wynik * a % MOD;
		}
		a = a * a % MOD;
		b /= 2;
	}
	return wynik;
}
 
ll silnia(int n) {
	ll wynik = 1;
	for (int i = 1; i <= n; i++) {
		wynik = (wynik * i) % MOD;
	}
	return wynik;
}
 
ll dwumian(int n, int k) {
	return silnia(n) * potega(silnia(k), MOD - 2) % MOD * potega(silnia(n - k), MOD - 2) % MOD;
}
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	int n, m;
	cin >> n >> m;
	cout << dwumian(n + m - 1, n - 1);
 
	return 0;
}

