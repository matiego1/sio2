#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

struct Kolejka {
	vector<ll> dodane;
	ll or_dodane = 0;
	vector<para> do_usuniecia;
	
	void push(ll e) {
		dodane.push_back(e);
		or_dodane |= e;
	}
	
	ll get() {
		return or_dodane | (do_usuniecia.empty() ? 0 : do_usuniecia.back().second);
	}
	
	void przenies_dodane() {
		while (!dodane.empty()) {
			ll e = dodane.back();
			dodane.pop_back();
			
			do_usuniecia.push_back({e, e | (do_usuniecia.empty() ? 0 : do_usuniecia.back().second)});
		}
		or_dodane = 0;
	}
	
	bool pop() {
		if (do_usuniecia.empty()) przenies_dodane();
		if (do_usuniecia.empty()) return false;
		do_usuniecia.pop_back();
		return true;
	}
	
	void clear() {
		dodane.clear();
		do_usuniecia.clear();
		or_dodane = 0;
	}
};

const int MAX = 2 * 1000 * 1000;
const int INF = MAX + 100;
ll wej[MAX + 1];
ll prawo[MAX + 1];
ll lewo[MAX + 1];
Kolejka kolejka;

ll indeks(ll x, int m) {
	if (x > m) return x % m;
	if (x <= 0) return m + x;
	return x;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	ll or_calosci = 0;
	
	for (int i = 1; i <= m; i++) {
		ll x;
		cin >> x;
		wej[i] = x | ((((1 << n) - 1) ^ x) << n);
		
		or_calosci |= wej[i];
	}
	
	// w prawo
	int pocz = 1;
	kolejka.push(wej[pocz]);
	for (int kon = 1; kon <= m; kon++) {
		while (pocz < kon || kolejka.get() != or_calosci) {
			pocz++;
			kolejka.push(wej[indeks(pocz, m)]);
		}
		
		if (kolejka.get() == or_calosci) {
			prawo[kon] = pocz - kon + 1;
		} else {
			prawo[kon] = INF;
		}
		
		kolejka.pop();
	}
	kolejka.clear();
	
	// w lewo
	pocz = m;
	kolejka.push(wej[pocz]);
	for (int kon = m; kon >= 1; kon--) {
		while (pocz > kon || kolejka.get() != or_calosci) {
			pocz--;
			kolejka.push(wej[indeks(pocz, m)]);
		}
		
		if (kolejka.get() == or_calosci) {
			lewo[kon] = kon - pocz + 1;
		} else {
			lewo[kon] = INF;
		}
		
		kolejka.pop();
	}
	
	ll wynik = 0;
	for (int i = 1; i <= m; i++) {
		if (lewo[i] + prawo[indeks(i + 1, m)] > m) continue;
		wynik += m - lewo[i] - prawo[indeks(i + 1, m)] + 1;
	}
	cout << wynik / 2;

	return 0;
}


