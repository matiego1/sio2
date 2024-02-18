#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

const int MAX = 100 * 1000;

vector<int> graf[MAX + 1];
int cena[MAX + 1];
int charyzma[MAX + 1];

int ojciec[MAX + 1];
multiset<int> wojownicy[MAX + 1];
int bilans[MAX + 1];

ll wynik = 0;

void dodaj(int ojciec, int x) {
	// Stac nas na dodanie x?
	if (bilans[ojciec] - x >= 0) {
		wojownicy[ojciec].insert(x);
		bilans[ojciec] -= x;
		return;
	}
	
	// Czy x jest wieksze od najwiekszego elementu?
	if (wojownicy[ojciec].empty()) return;
	auto ostatni = --wojownicy[ojciec].end();
	if (x >= *ostatni) return;
	
	// Usun najwiekszy element i w jego miejsce dodaj x
	bilans[ojciec] += *ostatni;
	bilans[ojciec] -= x;
	
	wojownicy[ojciec].erase(ostatni);
	wojownicy[ojciec].insert(x);
}

void dfs(int v) {
	// Znajdz najwieksze poddrzewo
	int maks = -1, maks_v = v;
	for (int u : graf[v]) {
		dfs(u);
		
		if ((int) wojownicy[ojciec[u]].size() > maks) {
			maks = (int) wojownicy[ojciec[u]].size();
			maks_v = ojciec[u];
		}
	}
	ojciec[v] = maks_v;
	
	// Dodaj wojownikow z mniejszy poddrzew do wiekszego
	dodaj(maks_v, cena[v]);
	for (int u : graf[v]) {
		if (ojciec[u] == maks_v) continue;
		
		for (int x : wojownicy[ojciec[u]]) {
			dodaj(maks_v, x);
		}
	}

	// Zaaktualizowanie wyniku
	wynik = max(wynik, (ll) wojownicy[maks_v].size() * charyzma[v]);
	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
		
	for (int i = 1; i <= n; i++) {
		int b, c, l;
		cin >> b >> c >> l;
		graf[b].push_back(i);
		cena[i] = c;
		charyzma[i] = l;
		bilans[i] = m;
	}

	dfs(1);
	
	cout << wynik;
	
	return 0;
}