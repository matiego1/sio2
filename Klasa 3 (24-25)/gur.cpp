#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
int wej[MAX + 1];
ll roznica[MAX + 1];
ll s, t;

ll koszt(ll x) {
	return -x * (x > 0 ? s : t);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q >> s >> t;
	
	ll wynik = 0;
	
	cin >> wej[0];
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		roznica[i] = wej[i] - wej[i - 1];
		wynik += koszt(roznica[i]);
	}
	
	while (q--) {
		int pocz, kon, x;
		cin >> pocz >> kon >> x;
		
		wynik -= koszt(roznica[pocz]);
		if (kon + 1 <= n) wynik -= koszt(roznica[kon + 1]);
		
		roznica[pocz] += x;
		roznica[kon + 1] -= x;
		
		wynik += koszt(roznica[pocz]);
		if (kon + 1 <= n) wynik += koszt(roznica[kon + 1]);
		
		cout << wynik << "\n";
	}

	return 0;
}

