#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<char, int> para;

const int MAX = 500 * 1000;
const int R = (1 << 19);
int tree[2 * R];
char wej[MAX + 1];
int ostatnie[MAX + 1];
char wynik[MAX + 1];

char query(int pocz, int kon) {
	pocz += R;
	kon += R;
	
	int maks = min(tree[pocz], tree[kon]);
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			maks = min(maks, tree[pocz + 1]);
		}
		if (kon % 2 == 1) {
			maks = min(maks, tree[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	return (char) maks;
}

void ustaw(int v, int wart) {
	v += R;
	tree[v] = wart;
	
	while (v > 1) {
		v /= 2;
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
}

int suma(int pocz, int kon) {
	pocz += R - 1;
	kon += R + 1;
	
	int w = 0;
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			w += tree[pocz + 1];
		}
		if (kon % 2 == 1) {
			w += tree[kon - 1];
		}
		pocz /= 2;
		kon /= 2;
	}
	return w;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		tree[i + R] = wej[i];
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	
	char maks = 'a';
	for (int pocz = 1; pocz + m - 1 <= n; pocz++) {
		maks = max(maks, query(pocz, pocz + m - 1));
	}
	
	for (int i = 1; i < 2 * R; i++) tree[i] = 0;
	
	for (int i = 1; i <= n; i++) {
		if (wej[i] < maks) {
			ustaw(i, 1);
		}
		if (wej[i] == maks) {
			ostatnie[i] = i;
		} else {
			ostatnie[i] = ostatnie[i - 1];
		}
	}
	
	for (int pocz = 1; pocz + m - 1 <= n; pocz++) {
		if (suma(pocz, pocz + m - 1) == 0) {
			ustaw(ostatnie[pocz + m - 1], 1);
		}
	}
	
	int rozmiar = 0;
	for (int i = 1; i <= n; i++) {
		if (tree[i + R]) {
			wynik[++rozmiar] = wej[i];
		}
	}
	
	sort(wynik + 1, wynik + 1 + rozmiar);
	
	for (int i = 1; i <= rozmiar; i++){
		cout << wynik[i];
	}
	
	return 0;
}

