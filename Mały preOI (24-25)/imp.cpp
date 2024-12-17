#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
ll wej[MAX + 1];

ll rozwiaz() {
	ll n, a, b;
	cin >> n >> a >> b;
	
	ll suma = 0;
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		suma += wej[i];
	}
	if (b == 0) return 0;
	
	// Podzadanie 1
	if (a == 0) return wej[n] * b;
	
	// Podzadanie 2
	ll wynik = suma * b;
	for (int i = 1; i < n; i++) {
		suma -= wej[i];
		ll poprzednie = (a + b) * wej[i];
		ll nastepne = (suma - wej[i] * (n - i)) * b;
		wynik = min(wynik, poprzednie + nastepne);
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

