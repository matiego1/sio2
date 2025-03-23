#include <iostream>
using namespace std;
typedef long long ll;

const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int R = (1 << 18);

ll tree[2 * R];
ll tree2[2 * R];

void push(int v) {
	if (tree2[v] != 0) {
		tree[2 * v] += tree2[v];
		tree2[2 * v] += tree2[v];
		tree[2 * v + 1] += tree2[v];
		tree2[2 * v + 1] += tree2[v];
		tree2[v] = 0;
	}
}

void add(int a, int b, int l, int r, int v, int x) {
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		tree[v] += x;
		tree2[v] += x;
	} else {
		push(v);
		add(a, b, l, (l + r) / 2, 2 * v, x);
		add(a, b, (l + r) / 2 + 1, r, 2 * v + 1, x);
		tree[v] = min(tree[2 * v], tree[2 * v + 1]);
	}
}

ll query(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return INF;
	if (a <= l && r <= b) return tree[v];
	push(v);
	return min(query(a, b, l, (l + r) / 2, 2 * v), query(a, b, (l + r) / 2 + 1, r, 2 * v + 1));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = R + n; i < 2 * R; i++) {
		tree[i] = INF;
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	
	const int POCZ = R, KON = 2 * R - 1;
	
	while (m--) {
		string typ;
		cin >> typ;
		int a, b;
		cin >> a >> b;
		a += R - 1;
		b += R - 1;
		if (typ == "budowa") {
			int c;
			cin >> c;
			
			if (a <= b) {
				add(a, b, POCZ, KON, 1, c);
			} else {
				add(R, b, POCZ, KON, 1, c);
				add(a, R + n - 1, POCZ, KON, 1, c);
			}
		} else {
			if (a <= b) {
				cout << query(a, b, POCZ, KON, 1) << "\n";
			} else {
				cout << min(query(R, b, POCZ, KON, 1), query(a, R + n - 1, POCZ, KON, 1)) << "\n";
			}
		}
	}

	return 0;
}