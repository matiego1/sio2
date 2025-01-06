#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
int wej[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	ll wynik = 0;
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		wynik += wej[i];
	}
	
	sort(wej + 1, wej + 1 + n);
	
	for (int lewy = 1, prawy = n; lewy < prawy; lewy++, prawy--) {
		wynik += max(0, wej[prawy] - wej[lewy]);
	}
	
	cout << wynik;

	return 0;
}

