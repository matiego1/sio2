#include <iostream>
#include <algorithm>
#include <set>
#define ll long long
using namespace std;

const int MAX = 10000;
pair<ll, ll> zasieg[MAX + 1];
set<int> wynik[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll n;
	int m, q;
	cin >> n >> m >> q;
	
	for (int i = 1; i < m; i++) {
		ll a;
		cin >> a;
		zasieg[i] = make_pair(zasieg[i - 1].second, a);
	}
	zasieg[m] = make_pair(zasieg[m - 1].second, n);
	
	for (int i = 1; i <= q; i++) {
		ll a;
		cin >> a;
		
		for (int j = 1; j <= m; j++) {
			if (zasieg[j].first <= a && a <= zasieg[j].second) {
				wynik[j].insert(i);
			}
		}
	}
	
	for (int i = 1; i <= m; i++) {
		for (int x : wynik[i]) {
			cout << x << " ";
		}
		cout << "\n";
	}
	
	return 0;
}
