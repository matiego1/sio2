#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll INF = LLONG_MAX;
vector<ll> czynniki;

void gen_czynniki(ll n) {
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			czynniki.push_back(i);
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	
	if (n > 1) {
		czynniki.push_back(n);
	}
}

ll ilosc(ll maks) {
	ll wynik = 0;
	for (int maska = 0; maska < (1 << czynniki.size()); maska++) {
		ll akt = maks;
		int znak = 1;
		for (int i = 0; i < (int) czynniki.size(); i++) {
			if (maska & (1 << i)) {
				akt /= czynniki[i];
				znak *= -1;
			}
		}
		wynik += akt * znak;
	}
	return wynik;
}

ll gen_pocz(ll k) {
	ll pocz = 1, kon = INF;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		ll wart = ilosc(srodek);
		if (wart < k) {
			pocz = srodek + 1;
		} else {
			kon = srodek;
		}
	}
	return pocz;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ll n, k;
	int c;
	cin >> n >> k >> c;
	
	gen_czynniki(n);
	
	ll akt = gen_pocz(k);
	while (c) {
		if (__gcd(n, akt) == 1) {
			cout << akt << " ";
			c--;
		}
		akt++;
	}
	
	return 0;
}
