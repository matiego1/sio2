#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int K = 300;
vector<int> graf[MAX + 1];

int wej[MAX + 1];
bool wylaczone[MAX + 1];
para dp1[MAX + 1][K + 5];
int rozmiar[MAX + 1];
int odwie[MAX + 1];
para akt[MAX + 1];
int dp2[MAX + 1];
int n;

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int sposob1(int pocz, int x) {
	for (int i = 1; i <= x; i++) {
		wej[i] = wczytaj();
		wylaczone[wej[i]] = true;
	}
	
	int wynik = -1;
	for (int i = 1; i <= rozmiar[pocz]; i++) {
		if (wylaczone[dp1[pocz][i].second]) continue;
		wynik = dp1[pocz][i].first;
		break;
	}
	
	for (int i = 1; i <= x; i++) {
		wylaczone[wej[i]] = false;
	}
	
	return wynik;
}

int sposob2(int pocz, int x) {
	for (int i = 1; i <= x; i++) {
		wej[i] = wczytaj();
		wylaczone[wej[i]] = true;
	}
	
	for (int v = 1; v <= n; v++) {
		if (wylaczone[v]) {
			dp2[v] = -1;
		} else {
			dp2[v] = 0;
		}
		
		for (int u : graf[v]) {
			if (dp2[u] == -1) continue;
			dp2[v] = max(dp2[v], dp2[u] + 1);
		}
	}
	
	for (int i = 1; i <= x; i++) {
		wylaczone[wej[i]] = false;
	}
	
	return dp2[pocz];
}

int main() {
	n = wczytaj();
	int m = wczytaj(), q = wczytaj();
	
	for (int i = 1; i <= m; i++) {
		int a = wczytaj(), b = wczytaj();
		graf[b].push_back(a);
	}
	
	int numer = 0;
	for (int v = 1; v <= n; v++) {
		rozmiar[v] = 1;
		dp1[v][1] = {0, v};
		
		for (int u : graf[v]) {
			int i1 = 1, i2 = 1;
			numer++;
			
			int nowy_rozmiar = 0;
			while (i1 <= rozmiar[v] && i2 <= rozmiar[u] && nowy_rozmiar < K + 1) {
				if (odwie[dp1[v][i1].second] == numer) {
					i1++;
					continue;
				}
				if (odwie[dp1[u][i2].second] == numer) {
					i2++;
					continue;
				}
				
				nowy_rozmiar++;
				if (dp1[v][i1].first > dp1[u][i2].first + 1) {
					akt[nowy_rozmiar] = dp1[v][i1];
					i1++;
				} else {
					akt[nowy_rozmiar] = dp1[u][i2];
					i2++;
					akt[nowy_rozmiar].first++;
				}
				odwie[akt[nowy_rozmiar].second] = numer;
			}
			
			while (nowy_rozmiar < K + 1 && i1 <= rozmiar[v]) {
				if (odwie[dp1[v][i1].second] == numer) {
					i1++;
					continue;
				}
				
				nowy_rozmiar++;
				akt[nowy_rozmiar] = dp1[v][i1];
				i1++;
				odwie[akt[nowy_rozmiar].second] = numer;
			}
			
			while (nowy_rozmiar < K + 1 && i2 <= rozmiar[u]) {
				if (odwie[dp1[u][i2].second] == numer) {
					i2++;
					continue;
				}
				
				nowy_rozmiar++;
				akt[nowy_rozmiar] = dp1[u][i2];
				i2++;
				akt[nowy_rozmiar].first++;
				odwie[akt[nowy_rozmiar].second] = numer;
			}
			
			for (int i = 1; i <= nowy_rozmiar; i++) {
				dp1[v][i] = akt[i];
			}
			rozmiar[v] = nowy_rozmiar;
		}
	}
	
	while (q--) {
		int pocz = wczytaj(), x = wczytaj();
		
		if (x <= K) {
			printf("%d\n", sposob1(pocz, x));
		} else {
			printf("%d\n", sposob2(pocz, x));
		}
	}

	return 0;
}

