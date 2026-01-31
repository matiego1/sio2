#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const ll MOD = 998244353;
const int BIT = 60;
const int MAX_trie = BIT * MAX + 15;
ll wej[MAX + 1];
map<ll, vector<ll>> mapa;
int n;
ll x;

struct Trie {
	int tab[MAX_trie][2];
	int ile[MAX_trie];
	int rozmiar = 0;
	
	void clear() {
		rozmiar = 0;
		tab[0][0] = 0;
		tab[0][1] = 0;
		ile[0] = 0;
	}
	
	ll wynik(ll a) {
		ll w = 0;
		int v = 0;

		for (ll bit = BIT; bit >= 0; bit--) {
			int bit_a = (a & (1ll << bit)) ? 1 : 0;
			int bit_x = (x & (1ll << bit)) ? 1 : 0;
			
			if (bit_a == 0 && bit_x == 0) {
				if (tab[v][1]) w += ile[tab[v][1]];
				v = tab[v][0];
			} else if (bit_a == 0 && bit_x == 1) {
				v = tab[v][1];
			} else if (bit_a == 1 && bit_x == 0) {
				if (tab[v][0]) w += ile[tab[v][0]];
				v = tab[v][1];
			} else {
				v = tab[v][0];
			}
			
			if (v == 0) break;
		}
		if (v) w += ile[v];
		
		return w;
	}
	
	void dodaj(ll a) {
		int v = 0;
		ile[v]++;
		
		for (int bit = BIT; bit >= 0; bit--) {
			int nast = (a & (1ll << bit)) ? 1 : 0;
			
			if (tab[v][nast] == 0) {
				rozmiar++;
				tab[v][nast] = rozmiar;
				
				tab[rozmiar][0] = 0;
				tab[rozmiar][1] = 0;
				ile[rozmiar] = 0;
			}
			
			v = tab[v][nast];
			ile[v]++;
		}
	}
} trie;

ll pot(ll a, ll b) {
	ll w = 1;
	while (b) {
		if (b & 1) {
			w = (w * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	return w;
}

ll grupa(vector<ll>& tab) {
	ll wynik = tab.size();
	trie.clear();
	
	for (ll wart : tab) {
		ll akt = trie.wynik(wart);
		wynik = (wynik + akt) % MOD;
		trie.dodaj(wart);
	}
	
	return wynik + 1;
}

void rozwiaz() {
	cin >> n >> x;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	if (x == 0) {
		cout << (pot(2, n) - 1 + MOD) % MOD << "\n";
		return;
	}
	
	int msb = 0;
	ll pom = x;
	while (pom) {
		pom /= 2;
		msb++;
	}
	ll maska = -1ll << msb;
	
	mapa.clear();
	for (int i = 1; i <= n; i++) {
		mapa[wej[i] & maska].push_back(wej[i]);
	}
	
	ll wynik = 1;
	
	for (auto& p : mapa) {
		wynik = wynik * grupa(p.second) % MOD;
	}
	
	cout << (wynik - 1 + MOD) % MOD << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int z;
	cin >> z;
	
	while (z--) {
		rozwiaz();
	}

	return 0;
}
