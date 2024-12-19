#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 2000;
ull wej[MAX + 5][MAX + 5];
ull suma_pozioma[MAX + 5];
ull suma_pionowa[MAX + 5];
ull wart_poziome[MAX + 5];
ull wart_pionowe[MAX + 5];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ull n, m;
	cin >> n >> m;
	
	for (ull y = 1; y <= n; y++) {
		for (ull x = 1; x <= m; x++) {
			cin >> wej[x][y];
			suma_pozioma[y] += wej[x][y];
			suma_pionowa[x] += wej[x][y];
		}
	}
	
	for (ull x = 0; x <= m; x++) {
		ull akt = 0;
		for (ull i = x, odle = 2; i >= 1; i--, odle += 4) {
			akt += odle * odle * suma_pionowa[i];
		}
		for (ull i = x + 1, odle = 2; i <= m; i++, odle += 4) {
			akt += odle * odle * suma_pionowa[i];
		}
		wart_pionowe[x] = akt;
	}
	
	for (ull y = 0; y <= n; y++) {
		ull akt = 0;
		for (ull i = y, odle = 2; i >= 1; i--, odle += 4) {
			akt += odle * odle * suma_pozioma[i];
		}
		for (ull i = y + 1, odle = 2; i <= n; i++, odle += 4) {
			akt += odle * odle * suma_pozioma[i];
		}
		wart_poziome[y] = akt;
	}
	
	ull wynik = wart_pionowe[0] + wart_poziome[0], wynik_x = 0, wynik_y = 0;
	for (ull y = 0; y <= n; y++) {
		for (ull x = 0; x <= m; x++) {
			ull akt = wart_pionowe[x] + wart_poziome[y];
			if (akt < wynik) {
				wynik = akt;
				wynik_x = x;
				wynik_y = y;
			}
		}
	}
	cout << wynik << "\n" << wynik_y << " " << wynik_x;
	
	return 0;
}
