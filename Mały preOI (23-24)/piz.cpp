#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 2 * 100 * 1000;
ll n;
ll wejA[MAX + 2];
ll wejB[MAX + 2];

ll podziel_sufit(ll a, ll b) {
	if (a % b == 0) {
		return a / b;
	}
	return (a / b) + 1;
}

ll policz_mniejsze(ll x) {
	ll wynik = 0;
	
	int ib = n + 1;
	for (int ia = 1; ia <= n + 1; ia++) {
		while (ib > 1 && podziel_sufit(x, wejA[ia]) <= wejB[ib]) {
			ib--;
		}
		
		if (podziel_sufit(x, wejA[ia]) > wejB[ib]) {
			wynik += ib;
		}
	}
	
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll a, b, k;
	cin >> a >> b >> n >> k;
	
	ll pop = 0, miniA = INF, maksA = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		
		wejA[i] = x - pop;
		pop = x;
		
		miniA = min(miniA, wejA[i]);
		maksA = max(maksA, wejA[i]);
	}
	wejA[n + 1] = a - pop;
	miniA = min(miniA, wejA[n + 1]);
	maksA = max(maksA, wejA[n + 1]);
	
	pop = 0;
	ll miniB = INF, maksB = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		
		wejB[i] = x - pop;
		pop = x;
		
		miniB = min(miniB, wejB[i]);
		maksB = max(maksB, wejB[i]);
	}
	wejB[n + 1] = b - pop;
	miniB = min(miniB, wejB[n + 1]);
	maksB = max(maksB, wejB[n + 1]);
	
	sort(wejA + 1, wejA + n + 2);
	sort(wejB + 1, wejB + n + 2);
	
	ll wszystkie = (n + 1) * (n + 1);
	ll pocz = miniA * miniB, kon = maksA * maksB;
	while (pocz < kon) {
		ll srodek = (pocz + kon + 1) / 2;
		if (wszystkie - policz_mniejsze(srodek) < k) {
			kon = srodek - 1;
		} else {
			pocz = srodek;
		}
	}
	
	cout << pocz;

	return 0;
}

