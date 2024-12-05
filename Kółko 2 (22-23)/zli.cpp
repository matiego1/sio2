#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MOD = 1000 * 1000 * 1000 + 7;
const int MAX = 100;
const int LOG = 60;
ll wej[LOG + 1][MAX][MAX];
ll pom[MAX];
ll macierz[MAX];

void pomnoz(ll (&m1)[MAX][MAX], ll (&m2)[MAX][MAX], ll (&wynik)[MAX][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			ll akt = 0;
			for (int k = 0; k < MAX; k++) {
				akt += m1[i][k] * m2[k][j];
				if (akt >= MOD) akt %= MOD;
			}
			wynik[i][j] = akt;
		}
	}
}

void pomnoz(ll (&m1)[MAX], ll (&m2)[MAX][MAX]) {
	for (int j = 0; j < MAX; j++) {
		ll akt = 0;
		for (int k = 0; k < MAX; k++) {
			akt += m1[k] * m2[k][j];
			if (akt >= MOD) akt %= MOD;
		}
		pom[j] = akt;
	}
	swap(m1, pom);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, z;
	cin >> n >> m >> z;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		wej[0][a - 1][b - 1] = 1;
	}

	for (int i = 1; i <= LOG; i++) {
		pomnoz(wej[i - 1], wej[i - 1], wej[i]);
	}
	
	for (int i = 1; i <= z; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		
		for (int j = 0; j < MAX; j++) {
			macierz[j] = 0;
		}
		macierz[a - 1] = 1;
		
		int indeks = 0;
		while (c) {
			if (c & 1) {
				pomnoz(macierz, wej[indeks]);
			}
			indeks++;
			c /= 2;
		}
		
		cout << macierz[b - 1] << "\n";
	}
	

	return 0;
}


