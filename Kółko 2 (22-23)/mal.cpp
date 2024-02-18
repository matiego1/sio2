#include <iostream>
#include <map>
using namespace std;

struct Zapyt {
	char typ;
	int pocz, kon;
	
	static Zapyt nowe(char typ, int pocz, int kon) {
		Zapyt z;
		z.typ = typ;
		z.pocz = pocz;
		z.kon = kon;
		return z;
	}
};

const int R = (1 << 20);
pair<int, int> tree[2 * R]; //<ile bialych, rozmiar>
bool tree2[2 * R];

const int MAX = 2 * 100 * 1000;
Zapyt zapyt[MAX];
map<int, int> mapa;

void flip(int v) {
	tree[v].first = tree[v].second - tree[v].first;
}

void push(int v) {
	if (tree2[v]) {
		flip(2 * v);
		flip(2 * v + 1);
		tree2[2 * v] = !tree2[2 * v];
		tree2[2 * v + 1] = !tree2[2 * v + 1];
		tree2[v] = false;
	}
}

//a, b - przedzial do aktualizacji
//l, r - przedzial za ktory odpowiada wierzcholek v
//v - aktualny wierzcholek
void zmien(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		flip(v);
		tree2[v] = !tree2[v];
	} else {
		push(v);
		zmien(a, b, l, (l + r) / 2, 2 * v);
		zmien(a, b, (l + r) / 2 + 1, r, 2 * v + 1);
		tree[v].first = tree[2 * v].first + tree[2 * v + 1].first;
	}
}

int query(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return 0;
	if (a <= l && r <= b) return tree[v].first;
	push(v);
	return query(a, b, l, (l + r) / 2, 2 * v) + query(a, b, (l + r) / 2 + 1, r, 2 * v + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		char typ;
		cin >> typ;
		int a, b;
		cin >> a >> b;
		zapyt[i] = Zapyt::nowe(typ, a, b);
		mapa[a] = 0;
		mapa[b] = 0;
	}
	
	int index = R;
	int pop = -1;
	for (auto p : mapa) {
		if (pop != -1 && p.first - pop - 1 > 0) {
			tree[index++] = make_pair(p.first - pop - 1, p.first - pop - 1);
		}
		pop = p.first;

		tree[index] = make_pair(1, 1);
		mapa[p.first] = index;
		index++;
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i].first = tree[2 * i].first + tree[2 * i + 1].first;
		tree[i].second = tree[2 * i].second + tree[2 * i + 1].second;
	}
	
	const int POCZ = R;
	const int KON = 2 * R - 1;
	
	for (int i = 0; i < m; i++) {
		Zapyt z = zapyt[i];
		if (z.typ == '?') {
			cout << query(mapa[z.pocz], mapa[z.kon], POCZ, KON, 1) << "\n";
		} else {
			zmien(mapa[z.pocz], mapa[z.kon], POCZ, KON, 1);
		}
	}

	return 0;
}

