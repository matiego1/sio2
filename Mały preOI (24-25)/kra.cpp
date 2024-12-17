#include "kralib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
int pary[MAX + 1];
int trojki[MAX + 1];
int znaki[MAX + 1];
vector<int> wynik;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n = init();
	wynik.resize(n);
	
	for (int i = 0; i <= n - 2; i++) {
		pary[i] = RoznicaCzapek(i, i + 1);
	}
	for (int i = 0; i <= n - 3; i++) {
		trojki[i] = RoznicaCzapek(i, i + 2);
	}
	
	znaki[1] = -1;
	for (int i = 2; i <= n - 1; i++) {
		if (pary[i - 2] + pary[i - 1] == trojki[i - 2]) {
			znaki[i] = znaki[i - 1];
		} else {
			znaki[i] = -znaki[i - 1];
		}
	}
	
	ll mini = 0, mini_i = 0;
	ll maks = 0, maks_i = 0;
	ll pref = 0;
	for (int i = 1; i <= n - 1; i++) {
		pref = pref + znaki[i] * pary[i - 1];
		if (pref < mini) {
			mini = pref;
			mini_i = i;
		}
		if (pref > maks) {
			maks = pref;
			maks_i = i;
		}
	}
	
	int znak = 1;
	if (mini_i > maks_i) {
		znak = -1;
		swap(mini_i, maks_i);
	}
	
	wynik[mini_i] = 0;
	for (int i = mini_i - 1; i >= 0; i--) {
		wynik[i] = wynik[i + 1] - znak * znaki[i + 1] * pary[i];
	}
	for (int i = mini_i + 1; i <= n - 1; i++) {
		wynik[i] = wynik[i - 1] + znak * znaki[i] * pary[i - 1];
	}
	
	Odpowiedz(wynik);

	return 0;
}

