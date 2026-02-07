#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

vector<para> elementy;
vector<ll> jedynki;

ll rekur(ll pojemnosc) {
	if (pojemnosc <= 0 || elementy.empty()) return 0;
	
	while (elementy.size() && elementy.back().first == 1) {
		jedynki.push_back(elementy.back().second);
		elementy.pop_back();
	}
	sort(jedynki.begin(), jedynki.end());
	
	ll p, ile_jedynek;
	if (elementy.size()) {
		p = elementy.back().first;
		ile_jedynek = min((ll) jedynki.size(), pojemnosc % p);
	} else {
		p = pojemnosc + 1;
		ile_jedynek = min((ll) jedynki.size(), pojemnosc);
	}
	
	ll wynik = 0;
	while (ile_jedynek--) {
		wynik += jedynki.back();
		jedynki.pop_back();
	}
	
	pojemnosc /= p;
	for (para& e : elementy) {
		e.first /= p;
	}
	
	ll grupa = 0, ile = 0;
	while (jedynki.size()) {
		grupa += jedynki.back();
		jedynki.pop_back();
		ile++;
		
		if (ile == p) {
			elementy.push_back({1, grupa});
			grupa = 0;
			ile = 0;
		}
	}
	if (ile) elementy.push_back({1, grupa});
	
	return wynik + rekur(pojemnosc);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ll n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		ll wart, masa;
		cin >> wart >> masa;
		elementy.push_back({masa, wart});
	}
	sort(elementy.begin(), elementy.end(), greater());
	
	m /= elementy.back().first;
	for (para& e : elementy) {
		e.first /= elementy.back().first;
	}
	
	cout << rekur(m);

	return 0;
}

