#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1000 * 2;
pair<int, int> ciecia[MAX]; //0 - pionowe, 1 - poziome

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	int k = n + m - 2;
	
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		ciecia[i] = make_pair(a, i >= n - 1);
	}
	
	sort(ciecia, ciecia + k);
	
	int wynik = 0;
	int pionowe = 1, poziome = 1;
	for (int i = k - 1; i >= 0; i--) {
		if (ciecia[i].second == 0) {
			poziome++;
			wynik += ciecia[i].first * pionowe;
		} else {
			pionowe++;
			wynik += ciecia[i].first * poziome;
		}
	}
	
	cout << wynik;

	return 0;
}

