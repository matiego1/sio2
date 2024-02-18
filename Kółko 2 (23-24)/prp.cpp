#include <iostream>
using namespace std;
typedef long long ll;

const int MOD = 1000 * 1000 * 1000 + 7;
const int R = (1 << 18);
ll tree[2 * R];

void pomnoz(int a, int b, ll x) {
	a += R;
	b += R;
	
	tree[a] = (tree[a] * x) % MOD;
	if (a != b) {
		tree[b] = (tree[b] * x) % MOD;
	}
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			tree[a + 1] = (tree[a + 1] * x) % MOD;
		}
		if (b % 2 == 1) {
			tree[b - 1] = (tree[b - 1] * x) % MOD;
		}
		a /= 2;
		b /= 2;
	}
}

ll podaj(int index) {
	index += R;
	ll wynik = 1;
	while (index >= 1) {
		wynik = (wynik * tree[index]) % MOD;
		index /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for (int i = 0; i < 2 * R; i++) {
		tree[i] = 1;
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b;
		cin >> a >> b;
		
		if (a == 0) {
			int c, d;
			cin >> c >> d;
			pomnoz(b, c, d);
		} else {
			cout << podaj(b) << "\n";
		}
	}

	return 0;
}
