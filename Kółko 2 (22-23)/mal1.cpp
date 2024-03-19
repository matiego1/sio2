#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;

bool sito[MAX + 1];
int min_dzielnik[MAX + 1];
vector<int> rozklad[MAX + 1];
int wystapienia[MAX + 1];
int liczba_zapalonych[MAX + 1];

void generuj_sito(int n) {
	min_dzielnik[1] = 1;
	sito[2] = true;
	for (int i = 3; i <= n; i += 2) {
		sito[i] = true;
	}
	for (int i = 2; i <= n; i += 2) {
		min_dzielnik[i] = 2;
	}
	for (int i = 3; i <= n; i += 2) {
		if (sito[i]) {
			min_dzielnik[i] = i;
			for (ll j = i; j * i <= n; j += 2) {
				if (sito[j * i]) {
					sito[j * i] = false;
					min_dzielnik[j * i] = i;
				}
			}
		}
	}
}
void generuj_rozklad(int n) {
	for (int i = 2; i <= n; i++) {
		int x = i;
		while (x > 1) {
			if (rozklad[i].empty() || rozklad[i].back() != min_dzielnik[x]) {
				rozklad[i].push_back(min_dzielnik[x]);
			}
			x /= min_dzielnik[x];
		}
	}
}
int dzielnik_z_maski(int x, int maska) {
	int wynik = 1;
	for (int i = 0; i < (int) rozklad[x].size(); i++) {
		if (maska & (1 << i)) {
			wynik *= rozklad[x][i];
		}
	}
	return wynik;
}
void generuj_wystapienia(int n) {
	for (int i = 2; i <= n; i++) {
		for (int maska = 1; maska < (1 << (int) rozklad[i].size()); maska++) {
			wystapienia[dzielnik_z_maski(i, maska)]++;
		}
	}
}
void generuj_liczba_zapalonych(int n) {
	for (int i = 1; i <= n; i++) {
		liczba_zapalonych[i] = (i & 1) + liczba_zapalonych[i / 2];
	}
}
int policz_nie_wzglednie_pierwsze(int x) {
	int wynik = 0;
	for (int maska = 1; maska < (1 << (int) rozklad[x].size()); maska++) {
		wynik += (liczba_zapalonych[maska] % 2 == 0 ? -1 : 1) * wystapienia[dzielnik_z_maski(x, maska)];
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	generuj_sito(n);
	generuj_rozklad(n);
	generuj_wystapienia(n);
	generuj_liczba_zapalonych(n);
	
	ll wynik = (ll) n * n + 2;
	for (int i = 2; i <= n; i++) {
		wynik -= policz_nie_wzglednie_pierwsze(i);
	}
	
	cout << wynik;

	return 0;
}
