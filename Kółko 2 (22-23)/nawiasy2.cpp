#include <iostream>
#include <climits>
using namespace std;

const int R = (1 << 17);
const int INF = INT_MAX;
int tree[2 * R];
int tree2[2 * R];

void push(int v, int n) {
	tree[2 * v] += tree2[v];
	tree2[2 * v] += tree2[v];
	tree[2 * v + 1] += tree2[v];
	tree2[2 * v + 1] += tree2[v];
	tree2[v] = 0;
}

//a, b - przedzia³ aktualizowany
//l, r - przedzia³ za który odpowiada wierzcho³ek v
//v - aktualny wierzcho³ek
//x - wartoœæ do dodania
void add(int a, int b, int l, int r, int v, int x) {
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		tree[v] += x;
		tree2[v] += x;
	} else {
		push(v, r - l + 1);
		add(a, b, l, (l + r) / 2, 2 * v, x);
		add(a, b, (l + r) / 2 + 1, r, 2 * v + 1, x);
		tree[v] = min(tree[2 * v], tree[2 * v + 1]);
	}
}

int query(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return INF;
	if (a <= l && r <= b) return tree[v];
	push(v, r - l + 1);
	return min(query(a, b, l, (l + r) / 2, 2 * v), query(a, b, (l + r) / 2 + 1, r, 2 * v + 1));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	int tab[n + 3];
	
	int suma = 0;
	for (int i = 0; i < n; i++) {
		cin >> tab[i];
		suma += tab[i];
		tree[R + i] = suma;
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	
	int a;
	cin >> a;
	const int POCZ = R;
	const int KON = 2 * R - 1;
	while (a != -1) {
		if (a == 0) {
			if (query(POCZ, KON, POCZ, KON, 1) == 0 && query(KON, KON, POCZ, KON, 1) == 0) {
				cout << "TAK\n";
			} else {
				cout << "NIE\n";
			}
		} else {
			a--;
			if (tab[a] == -1) {
				add(R + a, KON, POCZ, KON, 1, 2);
			} else {
				add(R + a, KON, POCZ, KON, 1, -2);
			}
			tab[a] *= -1;
		}
		cin >> a;
	}
	
	return 0;
}
