#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Node {
	int rozmiar = 1;
	ll suma_a, suma_b, suma;
	ll push_a, push_b;
};

const int MOD = 1000 * 1000 * 1000 + 7;
const int R = (1 << 17);
Node tree[2 * R];

void dodaj_a(int v, ll x) {
	tree[v].suma_a = (tree[v].suma_a + ((tree[v].rozmiar * x) % MOD)) % MOD;
	tree[v].suma = (tree[v].suma + ((tree[v].suma_b * x) % MOD)) % MOD;
	tree[v].push_a = (tree[v].push_a + x) % MOD;
}
void dodaj_b(int v, ll x) {
	tree[v].suma_b = (tree[v].suma_b + ((tree[v].rozmiar * x) % MOD)) % MOD;
	tree[v].suma = (tree[v].suma + ((tree[v].suma_a * x) % MOD)) % MOD;
	tree[v].push_b = (tree[v].push_b + x) % MOD;
}

void push(int v) {
	if (tree[v].push_a > 0) {
		dodaj_a(2 * v, tree[v].push_a);
		dodaj_a(2 * v + 1, tree[v].push_a);
		tree[v].push_a = 0;
	}
	if (tree[v].push_b > 0) {
		dodaj_b(2 * v, tree[v].push_b);
		dodaj_b(2 * v + 1, tree[v].push_b);
		tree[v].push_b = 0;
	}
}

void add(int a, int b, int l, int r, int v, ll x, bool czy_a) {
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		if (czy_a) {
			dodaj_a(v, x);
		} else {
			dodaj_b(v, x);
		}
	} else {
		push(v);
		add(a, b, l, (l + r) / 2, 2 * v, x, czy_a);
		add(a, b, (l + r) / 2 + 1, r, 2 * v + 1, x, czy_a);
		tree[v].suma_a = (tree[2 * v].suma_a + tree[2 * v + 1].suma_a) % MOD;
		tree[v].suma_b = (tree[2 * v].suma_b + tree[2 * v + 1].suma_b) % MOD;
		tree[v].suma = (tree[2 * v].suma + tree[2 * v + 1].suma) % MOD;
	}
}

ll query(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return 0;
	if (a <= l && r <= b) return tree[v].suma;	
	push(v);
	return (query(a, b, l, (l + r) / 2, 2 * v) + query(a, b, (l + r) / 2 + 1, r, 2 * v + 1)) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i].rozmiar = tree[2 * i].rozmiar + tree[2 * i + 1].rozmiar;
	}
	
	const int POCZ = R;
	const int KON = 2 * R - 1;
	
	while (q--) {
		char c;
		cin >> c;
		int a, b;
		cin >> a >> b;
		if (c == '?') {
			cout << query(R + a, R + b, POCZ, KON, 1) << "\n";
		} else {
			int x;
			cin >> x;
			add(R + a, R + b, POCZ, KON, 1, x, (c == '*'));
		}
	}
	

	return 0;
}


