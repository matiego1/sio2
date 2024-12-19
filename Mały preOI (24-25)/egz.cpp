#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
int wej[MAX + 1];
const int R = (1 << 18);
unordered_map<int, int> tree[2 * R];

int query(int pocz, int kon, int x) {
	pocz += R;
	kon += R;
	int wynik = tree[pocz][x];
	if (pocz != kon) wynik += tree[kon][x];
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik += tree[pocz + 1][x];
		}
		if (kon % 2 == 1) {
			wynik += tree[kon - 1][x];
		}
		pocz /= 2;
		kon /= 2;
	}
	return wynik;
}

void zmien(int indeks, int x, int wart) {
	indeks += R;
	tree[indeks][x] += wart;
	while (indeks > 1) {
		indeks /= 2;
		tree[indeks][x] += wart;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		zmien(i, wej[i], 1);
	}
	
	while (q--) {
		char c;
		cin >> c;
		
		if (c == '?') {
			int pocz, kon, x;
			cin >> pocz >> kon >> x;
			
			cout << query(pocz, kon, x) << "\n";
		} else {
			int poz, x;
			cin >> poz >> x;
			
			zmien(poz, wej[poz], -1);
			wej[poz] = x;
			zmien(poz, wej[poz], 1);
		}
	}
	
	return 0;
}

