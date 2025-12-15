#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int MAX_K = 20;
const int MAX_ai = 10 * 1000 * 1000;

int sito[MAX_ai + 1];
int wej[MAX + 1];
int ostatnie[MAX + 1][MAX_K + 1];
int dp[MAX + 1][MAX_K + 1];
int zlicz[MAX_ai + 1];
int n;

void generuj_sito() {
	for (int i = 1; i <= MAX_ai; i++) sito[i] = i;

	for (int i = 2; i * i <= MAX_ai; i++) {
		if (sito[i] == i) {
			for (int j = i; j <= MAX_ai; j += i) {
				if (sito[j] == j) {
					sito[j] = i;
				}
			}
		}
	}
}

int popraw(int x) {
	if (x == 1) return 1;
	int wynik = 1;
	int akt = x, ile = 0;
	while (x > 1) {
		if (sito[x] == akt) {
			ile++;	
		} else {
			if (ile & 1) wynik *= akt;
			ile = 1;
			akt = sito[x];
		}
		x /= sito[x];
	}
	if (ile & 1) wynik *= akt;
	return wynik;
}

void gasienica(int t) {
	int lewy = 1;
	int koszt = 0;
	for (int prawy = 1; prawy <= n; prawy++) {
		zlicz[wej[prawy]]++;
		if (zlicz[wej[prawy]] > 1) koszt++;
		
		while (koszt > t && lewy < prawy) {
			zlicz[wej[lewy]]--;
			if (zlicz[wej[lewy]] >= 1) koszt--;
			lewy++;
		}
		
		ostatnie[prawy][t] = lewy;
	}
	
	for (int i = 1; i <= n; i++) zlicz[wej[i]] = 0;
} 

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	generuj_sito();
	
	n = wczytaj();
	int k = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		int a = wczytaj();
		wej[i] = popraw(a);
	}
	
	for (int i = 0; i <= k; i++) {
		gasienica(i);
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = INT_MAX;
			for (int t = 0; t <= j; t++) {
				dp[i][j] = min(dp[i][j], 1 + dp[ostatnie[i][t] - 1][j - t]);
			}
		}
	}
	
	int wynik = dp[n][0];
	for (int i = 1; i <= k; i++) {
		wynik = min(wynik, dp[n][i]);
	}
	cout << wynik;
	
	return 0;
}

