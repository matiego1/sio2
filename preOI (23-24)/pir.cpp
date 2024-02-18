#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 200 * 1000;
int wej[MAX];
int posortowane[MAX];
int tab[MAX];

bool sprawdz(int n, int x) {
	for (int i = 1; i <= 2 * n - 1; i++) {
		tab[i] = (wej[i] >= x);
	}
	for (int i = 0; i <= n - 2; i++) {
		if (tab[n + i] == tab[n + i + 1]) return tab[n + i];
		if (tab[n - i] == tab[n - i - 1]) return tab[n - i];
	}
	return tab[1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i <= 2 * n - 1; i++) {
		cin >> wej[i];
		posortowane[i] = wej[i];
	}
	
	sort(posortowane + 1, posortowane + n + n);
	
	int pocz = 1, kon = 2 * n - 1;
	while (pocz < kon) {
		int srodek = (pocz + kon + 1) / 2;
		if (sprawdz(n, posortowane[srodek])) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
		}
	}
	cout << posortowane[pocz];

	return 0;
}
