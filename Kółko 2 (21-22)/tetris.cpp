#include <iostream>
using namespace std;

const int R = (1 << 20);
int tree[2 * R];
int tree2[2 * R];

void push(int v) {
	if (tree2[v] != 0) {
		tree[2 * v] = tree2[v];
		tree2[2 * v] = tree2[v];
		tree[2 * v + 1] = tree2[v];
		tree2[2 * v + 1] = tree2[v];
		tree2[v] = 0;
	}
}

void set(int a, int b, int l, int r, int v, int x) {
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		tree[v] = x;
		tree2[v] = x;
	} else {
		push(v);
		set(a, b, l, (l + r) / 2, 2 * v, x);
		set(a, b, (l + r) / 2 + 1, r, 2 * v + 1, x);
		tree[v] = max(tree[2 * v], tree[2 * v + 1]);
	}
}

int query(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return 0;
	if (a <= l && r <= b) return tree[v];
	push(v);
	return max(query(a, b, l, (l + r) / 2, 2 * v), query(a, b, (l + r) / 2 + 1, r, 2 * v + 1));
	
}

int main() {
	int d, n;
	cin >> d >> n;
	
	const int POCZ = R;
	const int KON = 2 * R - 1;
	while (n--) {
		int l, x;
		cin >> l >> x;
		set(R + x, R + x + l - 1, POCZ, KON, 1, query(R + x, R + x + l - 1, POCZ, KON, 1) + 1);
	}
	
	cout << query(POCZ, KON, POCZ, KON, 1);
	
	return 0;
}