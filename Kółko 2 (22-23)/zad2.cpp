#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 250 * 1000;
const int R = (1 << 18);
int B[MAX + 1];
int kolej[MAX + 1];
ll suma[2 * R + 1];
int ost[2 * R + 1];

void ustaw(int indeks, ll x) {
	indeks += R;
	suma[indeks] = x;
	
	if (x > 0) {
		ost[indeks] = indeks;
	} else {
		ost[indeks] = -INF;
	}
	
	while (indeks > 1) {
		indeks /= 2;
		suma[indeks] = suma[2 * indeks] + suma[2 * indeks + 1];
		ost[indeks] = max(ost[2 * indeks], ost[2 * indeks + 1]);
	}
}

ll suma_pref(int indeks) {
	indeks += R;
	ll wynik = suma[indeks];
	while (indeks > 1) {
		if (indeks % 2 == 1) {
			wynik += suma[indeks - 1];
		}
		indeks /= 2;
	}
	return wynik;
}

int ostatni(int indeks) {
	indeks += R;
	int wynik = ost[indeks];
	while (indeks > 1) {
		if (indeks % 2 == 1) {
			wynik = max(wynik, ost[indeks - 1]);
		}
		indeks /= 2;
	}
	return wynik - R;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i < 2 * R; i++) {
		ost[i] = -INF;
	} 
	
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		ustaw(i, a);
		kolej[i] = i;
	}
	for (int i = 1; i <= n; i++) {
		cin >> B[i];
	}
	
	sort(kolej + 1, kolej + 1 + n, [](int a, int b) { return B[a] < B[b]; });
	
	int wynik = 0;
	
	for (int i = 1; i <= n; i++) {
		ll a = suma_pref(kolej[i]);
		ll b = B[kolej[i]];
		
		if (b > a) continue;
		wynik++;
		
		int j = kolej[i];
		while (b > 0) {
			j = ostatni(j);
			if (b <= suma[R + j]) {
				ustaw(j, suma[R + j] - b);
				b = 0;		
			} else {
				b -= suma[R + j];
				ustaw(j, 0);
			}
			j--;
		}
		
	}
	cout << wynik;

	return 0;
}

