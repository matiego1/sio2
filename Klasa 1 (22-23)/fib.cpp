#include <iostream>
#define ll long long
using namespace std;

const int MOD = 1000 * 1000 * 1000 + 7;

void poczatek(ll m[2][2]) {
	m[0][0] = 1;
	m[0][1] = 1;
	m[1][0] = 1;
	m[1][1] = 0;
}
void kwadrat(ll m[2][2]) {
	ll a = ((m[0][0] * m[0][0]) % MOD + (m[0][1] * m[1][0]) % MOD) % MOD;
	ll b = ((m[1][1] * m[0][1]) % MOD + (m[0][0] * m[0][1]) % MOD) % MOD;
	ll c = ((m[1][1] * m[1][0]) % MOD + (m[0][0] * m[1][0]) % MOD) % MOD;
	ll d = ((m[1][1] * m[1][1]) % MOD + (m[0][1] * m[1][0]) % MOD) % MOD;
	m[0][0] = a;
	m[0][1] = b;
	m[1][0] = c;
	m[1][1] = d;
}
void pomnoz(ll m1[2][2], ll m2[2][2]) {
	ll a = ((m2[0][0] * m1[0][0]) % MOD + (m2[1][0] * m1[0][1]) % MOD) % MOD;
	ll b = ((m2[0][1] * m1[0][0]) % MOD + (m2[1][1] * m1[0][1]) % MOD) % MOD;
	ll c = ((m2[1][0] * m1[1][1]) % MOD + (m2[0][0] * m1[1][0]) % MOD) % MOD;
	ll d = ((m2[1][1] * m1[1][1]) % MOD + (m2[0][1] * m1[1][0]) % MOD) % MOD;
	m1[0][0] = a;
	m1[0][1] = b;
	m1[1][0] = c;
	m1[1][1] = d;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll b;
	cin >> b;
	
	if (b == 0) {
		cout << 0;
		return 0;	
	}
	b -= 1;
	
	ll a[2][2];
	ll wyn[2][2];
	poczatek(a);
	poczatek(wyn);
	
	while (b > 0) {
		if (b & 1) {
			pomnoz(wyn, a);
		}
		kwadrat(a);
		b /= 2;
	}
	cout << wyn[0][1];
	
	return 0;
}
