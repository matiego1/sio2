#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int, ll> para;

const int MAX = 2 * 100 * 1000;
const int MOD = 1000 * 1000 * 1000 + 7;
vector<int> graf[MAX + 1];

ll silnia(ll x) {
	ll wynik = 1;
	for (int i = 2; i <= x; i++) {
		wynik = (wynik * i) % MOD;
	}
	return wynik;
}

ll pot(ll a, ll b) {
	ll wynik = 1;
	while (b > 0) {
		if (b % 2 != 0) {
			wynik = (wynik * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	return wynik;
}

para dfs(int v, int ojciec) { // rozmiar poddrzewa, wynik
	int rozmiar = 0;
	ll wynik = 1;
	
	ll iloczyn = 1;
	
	for (int u : graf[v]) {
		if (u != ojciec) {
			para dziecko = dfs(u, v);
			
			rozmiar += dziecko.first;
			wynik = (wynik * dziecko.second) % MOD;
			
			iloczyn = (iloczyn * silnia(dziecko.first)) % MOD;
		}
	}
	
	wynik = (wynik * ((silnia(rozmiar) * pot(iloczyn, MOD - 2)) % MOD)) % MOD;
	
	return {rozmiar + 1, wynik};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	cout << dfs(1, 1).second;
	
	return 0;
}

