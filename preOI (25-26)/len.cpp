#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int R = (1 << 18);
int wej[MAX + 1];
int tree_poz[2 * R];
int tree_ile[2 * R];
int pozycje[MAX + 1];

void ustaw_poz(int i, int wart) {
	i += R;
	tree_poz[i] = wart;
	
	while (i > 1) {
		i /= 2;
		tree_poz[i] = max(tree_poz[2 * i], tree_poz[2 * i + 1]);
	}
}
int query_poz(int pocz, int kon) {
	pocz += R;
	kon += R;
	
	int w = max(tree_poz[pocz], tree_poz[kon]);
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			w = max(w, tree_poz[pocz + 1]);
		}
		if (kon % 2 == 1) {
			w = max(w, tree_poz[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	return w;
}

void ustaw_ile(int i, int wart) {
	i += R;
	tree_ile[i] = wart;
	
	while (i > 1) {
		i /= 2;
		tree_ile[i] = tree_ile[2 * i] + tree_ile[2 * i + 1];
	}
}
int query_ile(int pocz, int kon) {
	pocz += R - 1;
	kon += R + 1;
	
	int w = 0;
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			w += tree_ile[pocz + 1];
		}
		if (kon % 2 == 1) {
			w += tree_ile[kon - 1];
		}
		pocz /= 2;
		kon /= 2;
	}
	return w;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		tree_poz[wej[i] + R] = i;
		tree_ile[i + R] = 1;
		pozycje[wej[i]] = i;
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree_poz[i] = max(tree_poz[2 * i], tree_poz[2 * i + 1]);
		tree_ile[i] = tree_ile[2 * i] + tree_ile[2 * i + 1];
	}
	
	ll wynik = 0;
	for (int i = n; i >= 2; i--) {
		int maks1 = query_poz(1, i - 1);
		ustaw_poz(wej[maks1], 0);
		int kon = query_poz(1, i - 1);
		ustaw_poz(wej[maks1], maks1);
		
		int pocz = pozycje[i];
		if (kon <= pocz) continue;
		
		int akt = query_ile(pocz + 1, kon);
		wynik += akt;
		ustaw_ile(pocz, 0);
		ustaw_poz(i, 0);
	}
	
	cout << wynik;

	return 0;
}

