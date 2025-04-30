#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
 
const ll MOD = 1000 * 1000 * 1000 + 7;
const ll PODZIEL = 500000004;
 
ll suma(ll pocz, ll kon) {
	return (pocz + kon) % MOD * ((kon - pocz + 1) % MOD) % MOD * PODZIEL % MOD;
}
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	ll n;
	cin >> n;
	
	ll wynik = 0;
	
	ll d = 1;
	while (d <= n) {
		ll wart = n / d;
		
		ll pocz = d;
		ll kon = n / wart;
		
		wynik = (wynik + wart * suma(pocz, kon) % MOD) % MOD;
		d = kon + 1;
	}
	
	cout << wynik;
 
	return 0;
}

