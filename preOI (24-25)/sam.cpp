#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

struct Trojka {
	ll pocz, kon, dzien;
};
bool operator<(const Trojka& t1, const Trojka& t2) {
	if (t1.pocz == t2.pocz) {
		if (t1.kon == t2.kon) return t1.dzien < t2.dzien;
		return t1.kon < t2.kon;
	}
	return t1.pocz < t2.pocz;
}

const int MAX = 200 * 1000;
para zadanie[MAX + 1];
para zapyt[MAX + 1];
ll tab[MAX + 1];
ll wynik[MAX + 1];
multiset<Trojka> zbior;
int q;

void odp(ll ile, ll przerwa) {
	ll k = upper_bound(zapyt + 1, zapyt + 1 + q, przerwa, [](ll x, const para& p) {
		return x < p.first;
	}) - zapyt - 1;
	
	if (k > q) return;
	tab[k] += ile;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m >> q;
	
	for (int i = 1; i <= m; i++) {
		cin >> zadanie[i].first >> zadanie[i].second;
	}
	
	for (int i = 1; i <= q; i++) {
		cin >> zapyt[i].first;
		zapyt[i].second = i;
	}
	sort(zapyt + 1, zapyt + 1 + q);
	
	ll dzien = 0;
	for (int i = 1; i <= m; i++) {
		ll pocz = zadanie[i].first;
		ll kon = zadanie[i].second;
		dzien++;
		
		auto p = zbior.upper_bound({pocz, pocz, 0});
		while (p != zbior.end() && p->kon <= kon) {
			ll ile = p->kon - p->pocz + 1;
			ll przerwa = dzien + p->pocz - pocz - p->dzien - 1;
			odp(ile, przerwa);
			
			zbior.erase(p);
			
			p = zbior.upper_bound({pocz, pocz, 0});
		}
		
		if (p != zbior.end() && p->pocz <= kon) {
			ll ile = kon - p->pocz + 1;
			ll przerwa = dzien + p->pocz - pocz - p->dzien - 1;
			odp(ile, przerwa);
			
			zbior.insert({kon + 1, p->kon, p->dzien + kon + 1 - p->pocz});
			zbior.erase(p);
		}
		
		p = zbior.upper_bound({pocz, pocz, 0});
		if (p != zbior.begin()) {
			p--;
			if (p->kon >= pocz) {
				ll ile = min(p->kon, kon) - pocz + 1;
				ll przerwa = dzien - (p->dzien + pocz - p->pocz) - 1;
				odp(ile, przerwa);
				
				zbior.insert({p->pocz, pocz - 1, p->dzien});
				
				if (p->kon > kon) {
					zbior.insert({kon + 1, p->kon, p->dzien + kon + 1 - p->pocz});
				}
				
				zbior.erase(p);
			}
		}
		
		zbior.insert({pocz, kon, dzien});
		
		dzien += kon - pocz;
	}
	
	ll suma = 0;
	for (int i = q; i >= 1; i--) {
		suma += tab[i];
		wynik[zapyt[i].second] = suma;
	}
	
	for (int i = 1; i <= q; i++) {
		cout << wynik[i] << " ";
	}

	return 0;
}

