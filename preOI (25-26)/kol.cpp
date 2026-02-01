#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000 + 5;
const int K = 320;
int wej[MAX + 1];
vector<int> kolory[MAX];
vector<ll> pref[MAX];
ll ilosc[MAX];
ll suma[MAX];
ll wynik[K + 20][MAX + 20];
int ciezkie[MAX];
int n, m;

void policz_ciezki(int kolor, int indeks) {
	for (int i = 1; i <= n; i++) {
		ilosc[i] = 0;
		suma[i] = 0;
	}
	for (int i : kolory[kolor]) {
		ilosc[i] = 1;
		suma[i] = i;
	}
	for (int i = 1; i <= n; i++) {
		ilosc[i] += ilosc[i - 1];
		suma[i] += suma[i - 1];
	}
	
	for (int i = 1; i <= m; i++) {
		if (i == kolor) continue;
		
		wynik[indeks][i] = 0;
		for (ll poz : kolory[i]) {
			wynik[indeks][i] += ilosc[poz] * poz - suma[poz];
			wynik[indeks][i] += (suma[n] - suma[poz]) - (ilosc[n] - ilosc[poz]) * poz;
		}
	}
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

void rozwiaz() {
	n = wczytaj();
	m = wczytaj();
	int q = wczytaj();
	
	for (int i = 1; i <= m; i++) {
		kolory[i].clear();
		pref[i].clear();
		pref[i].push_back(0);
	}
	for (int i = 1; i <= n; i++) {
		wej[i] = wczytaj();
		
		kolory[wej[i]].push_back(i);
		pref[wej[i]].push_back(pref[wej[i]].back() + i);
	}
	
	int indeks = 0;
	for (int i = 1; i <= m; i++) {
		if ((int) kolory[i].size() > K) {
			ciezkie[i] = (++indeks);
			policz_ciezki(i, indeks);
		} else {
			ciezkie[i] = 0;
		}
	}
	
	while (q--) {
		int a = wczytaj(), b = wczytaj();
		
		if (ciezkie[a]) {
			printf("%lld\n", wynik[ciezkie[a]][b]);
		} else if (ciezkie[b]) {
			printf("%lld\n", wynik[ciezkie[b]][a]);
		} else {
			if (kolory[a].size() > kolory[b].size()) swap(a, b);
			
			ll w = 0;
			for (ll poz : kolory[a]) {
				ll i = lower_bound(kolory[b].begin(), kolory[b].end(), poz) - kolory[b].begin();
				w += i * poz - pref[b][i];
				w += (pref[b].back() - pref[b][i]) - ((ll) kolory[b].size() - i) * poz;
			}
			printf("%lld\n", w);
		}
	}
}

int main() {
	int z = wczytaj();
	
	while (z--) {
		rozwiaz();
	}

	return 0;
}
