#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int PRAWY_DOLNY = 1, LEWY_GORNY = 2, TRAWA = 3, OWCA = 4;
struct Wej {
	int x, y, indeks, typ;
};

const int MAX = 1000 * 1000;
const int R = (1 << 20);
Wej wej[3 * MAX + 1];
int wyniki[MAX + 1];
set<int> poziome;
int poprzednie[MAX + 1];
para tree[2 * R];

void push(int v, int l, int r) {
	if (r == l) return;
	
	if (tree[v].second) {
		tree[2 * v].second = true;
		tree[2 * v + 1].second = true;
		tree[2 * v].first = 0;
		tree[2 * v + 1].first = 0;
		tree[v].second = false;
	}
	
	if (tree[v].first) {
		tree[2 * v].first += tree[v].first;
		tree[2 * v + 1].first += tree[v].first;
		tree[v].first = 0;
	}
}

int query(int indeks, int v, int l, int r) {
	if (r == l) return tree[v].first;
	push(v, l, r);
	int srodek = (l + r) / 2;
	if (indeks <= srodek) {
		return query(indeks, 2 * v, l, srodek);
	} else {
		return query(indeks, 2 * v + 1, srodek + 1, r);
	}
}

void dodaj(int pocz, int kon, int wart, int v, int l, int r) {
	push(v, l, r);
	if (r < pocz || kon < l) return;
	if (pocz <= l && r <= kon) {
		tree[v].first += wart;
		return;
	}
	
	int srodek = (l + r) / 2;
	dodaj(pocz, kon, wart, 2 * v, l, srodek);
	dodaj(pocz, kon, wart, 2 * v + 1, srodek + 1, r);
}

void reset(int pocz, int kon, int v, int l, int r) {
	push(v, l, r);
	if (r < pocz || kon < l) return;
	if (pocz <= l && r <= kon) {
		tree[v].first = 0;
		tree[v].second = true;
		return;
	}
	
	int srodek = (l + r) / 2;
	reset(pocz, kon, 2 * v, l, srodek);
	reset(pocz, kon, 2 * v + 1, srodek + 1, r);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int indeks = 0;
	int f;
	cin >> f;
	for (int i = 1; i <= f; i++) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		wej[++indeks] = {x1 - 1, y1, y2, LEWY_GORNY};
		wej[++indeks] = {x2, y2, y1, PRAWY_DOLNY};
	}
	
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> y >> x;
		wej[++indeks] = {x, y, i, TRAWA};
	}
	
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> y >> x;
		wej[++indeks] = {x, y, i, OWCA};
	}
	
	poziome.insert(0);
	
	sort(wej + 1, wej + 1 + indeks, [](Wej& w1, Wej& w2) { return (w1.x == w2.x ? w1.typ < w2.typ : w1.x > w2.x); });
	
	const int V = 1, POCZ = 0, KON = R - 1;
	for (int i = 1; i <= indeks; i++) {
		Wej& w = wej[i];
		if (w.typ == OWCA) {
			wyniki[w.indeks] = query(w.y, V, POCZ, KON);
		} else if (w.typ == TRAWA) {
			auto granica = poziome.upper_bound(w.y);
			granica--;
			dodaj(*granica, w.y, 1, V, POCZ, KON);
		} else if (w.typ == PRAWY_DOLNY) {
			poprzednie[w.y + 1] = query(w.y + 1, V, POCZ, KON);
			
			reset(w.indeks, w.y, V, POCZ, KON);
			
			poziome.insert(w.y + 1);
			poziome.insert(w.indeks);
		} else {
			reset(w.y, w.indeks, V, POCZ, KON);
			
			poziome.erase(w.y);
			poziome.erase(w.indeks + 1);
			
			auto granica = poziome.upper_bound(w.y);
			granica--;
			int ile = query(w.indeks + 1, V, POCZ, KON);
			dodaj(w.y, w.indeks, ile, V, POCZ, KON);
			dodaj(*granica, w.y - 1, ile - poprzednie[w.indeks + 1], V, POCZ, KON);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << wyniki[i] << "\n";
	}

	return 0;
}
