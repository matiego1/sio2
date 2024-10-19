#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

struct Klocek {
	ll w, h;
};

const int MAX = 100 * 1000;
const ll MOD = 1000 * 1000 * 1000 + 7;
Klocek wej[MAX + 1];
stack<Klocek> s;

ll mod(ll x) {
	return x % MOD;
}

ll po2(ll x) {
	return mod(x * (x - 1) / 2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> wej[i].h;
	}
	for (int i = 1; i <= n; i++) {
		cin >> wej[i].w;
	}

	ll wynik = 0;
	ll koniec = 0;

	for (int i = 1; i <= n; i++) {
		wynik = mod(wynik + mod(po2(wej[i].w + 1) * po2(wej[i].h + 1)));

		ll w = 0;
		while (s.size() && s.top().h > wej[i].h) {
			koniec = mod(koniec - mod(po2(s.top().h + 1) * mod(s.top().w)) + MOD);
			w += s.top().w;
			s.pop();
		}
		if (w > 0) {
			koniec = mod(koniec + mod(po2(wej[i].h + 1) * mod(w)));
			s.push({w, wej[i].h});
		}

		wynik = mod(wynik + mod(koniec * mod(wej[i].w)));

		koniec = mod(koniec + mod(po2(wej[i].h + 1) * mod(wej[i].w)));

		s.push({wej[i].w, wej[i].h});
	}

	cout << wynik;
}
