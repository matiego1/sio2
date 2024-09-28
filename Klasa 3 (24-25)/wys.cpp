#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 50 * 1000;
int wej[MAX + 1];

int indeks(int p, int n) {
	if (p % n == 0) return n;
	return p % n;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	int prawo = 0, lewo = 0;
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		prawo += wej[i];
	}
	
	int wynik = -1;
	int p2 = 1;
	for (int p1 = 1; p1 <= n; p1++) {
		while (p2 <= p1 || lewo < prawo) {
			lewo += wej[indeks(p2, n)];
			prawo -= wej[indeks(p2, n)];
			p2++;
		}
		
		wynik = max(wynik, min(lewo, prawo));
		
		lewo -= wej[p1];
		prawo += wej[p1];
	}
	
	cout << wynik;

	return 0;
}


