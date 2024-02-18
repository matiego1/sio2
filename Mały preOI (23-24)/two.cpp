#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> para;

const int MAX = 2 * 100 * 1000;
int wej[MAX + 1];
para wyniki[MAX + 1]; //wynik dla platformy zaczynajacej sie w danej sniezce; numer ostatniej sniezki na platformie
int suff_maks[MAX + 1]; //maksymalny wynik (^^^) dla sniezek od i-tej do konca

int rozwiaz() {
	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		// nie jest to potrzebne
	}
	
	if (n <= 2) {
		return n;
	}
	
	sort(wej + 1, wej + n + 1);
	
	// Czy platformy moga przykryc wszystko
	if (wej[n] - wej[1] <= 2 * k) {
		return n;
	}
	
	// Policz tablice wyniki
	int koniec = 1;
	for (int i = 1; i <= n; i++) {
		while (koniec < n && wej[koniec + 1] - wej[i] <= k) {
			koniec++;
		}
		wyniki[i] = make_pair(koniec - i + 1, koniec);
	}
	
	// Policz tablice suff_maks
	suff_maks[n] = wyniki[n].first;
	for (int i = n - 1; i >= 1; i--) {
		suff_maks[i] = max(suff_maks[i + 1], wyniki[i].first);
	}
	
	// Policz wynik
	int wynik = -1;
	for (int i = 1; i <= n; i++) {
		int nastepny = wyniki[i].second + 1;
		if (nastepny <= n) {
 			wynik = max(wynik, wyniki[i].first + suff_maks[nastepny]);
		} else {
			wynik = max(wynik, wyniki[i].first);
		}
	}
	
	return wynik;
	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		cout << rozwiaz() << "\n";
	}

	return 0;
}