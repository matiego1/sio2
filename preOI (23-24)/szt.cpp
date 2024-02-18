#include <iostream>
#include <map>
using namespace std;
typedef long long ll;

const int MAX = 100 * 1000;
ll poz[MAX + 1];
int permutacja[MAX + 1];
int wynik[MAX + 1];

int pom[MAX + 1];
void pomnoz(int n, int* a, int* b) {
	for (int i = 1; i <= n; i++) {
		pom[i] = a[b[i]];
	}
	for (int i = 1; i <= n; i++) {
		a[i] = pom[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> poz[i];
		permutacja[i] = i;
	}
	
	int q;
	cin >> q;
	ll m;
	cin >> m;
	
	for (int i = 1; i <= q; i++) {
		int x;
		cin >> x;
		swap(permutacja[x], permutacja[x - 1]);
	}
	
	for (int i = 1; i < n; i++) {
		wynik[i] = permutacja[i];
	}
	m--;
	
	while (m > 0) {
		if (m % 2 == 1) {
			pomnoz(n - 1, wynik, permutacja);
		}
		pomnoz(n - 1, permutacja, permutacja);
		m /= 2;
	}
	
	
	ll x = poz[1];
	for (int i = 1; i < n; i++) {
		cout << x << " ";
		x += poz[wynik[i] + 1] - poz[wynik[i]];
	}
	cout << x;
	
	return 0;
}
