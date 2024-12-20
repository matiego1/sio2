#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int MAX = 100 * 1000;
ll D[MAX + 1];
para wej[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> D[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> wej[i].first;
	}
	for (int i = 1; i <= n; i++) {
		cin >> wej[i].second;
	}
	
	cin >> wej[0].first >> wej[0].second;
	
	ll suma = 0;
	for (int i = n; i >= 0; i--) {
		wej[i].first += suma;
		wej[i].second += suma;
		suma += D[i];
	}
	
	sort(wej + 1, wej + 1 + n);
	
	ll wynik = 0, mini_b = wej[0].second;
	for (int i = 1; i <= n; i++) {
		ll a = min(wej[0].first, wej[i].first);
		ll b = mini_b;
		wynik = max(wynik, a + b);
		mini_b = min(mini_b, wej[i].second);
	}
	cout <<  max(wynik, mini_b + wej[0].first);
	
	return 0;
}

