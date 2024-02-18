#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAX = 1000 * 1000;
pair<ll, ll> wej[MAX]; 
int k;

bool porownaj1(pair<ll, ll> &a, pair<ll, ll> &b) {
	return k * a.first + a.second > k * b.first + b.second;
}
bool porownaj2(pair<ll, ll> &a, pair<ll, ll> &b) {
	return a.first > b.first;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n >> k;
	
	for (int i = 0; i < n; i++) {
		ll a, b;
		cin >> a >> b;
		wej[i] = make_pair(a, b);
	}
	
	sort(wej, wej + n, &porownaj1);
	sort(wej, wej + min(k, n), &porownaj2);
	
	ll wynik = -1;
	for (int i = 0; i < min(k, n); i++) {
		wynik = max(wynik, i * wej[i].first);
	}
	for (int i = k; i < n; i++) {
		wynik = max(wynik, k * wej[i].first + wej[i].second);
	}

	cout << wynik;

	return 0;
}

