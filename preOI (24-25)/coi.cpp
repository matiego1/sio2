#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_N = 200 * 1000;
const int MAX_M = 800 * 1000;
const int R = (1 << 18);
const int POCZ = R;
const int KON = 2 * R - 1;
vector<int> graf[MAX_N + 1];
para krawedzie[MAX_M + 1];
int poziom[MAX_N + 1];
int numer[MAX_N + 1];
int nast[MAX_N + 5];
int pop[MAX_N + 5];
int wynik[MAX_N + 5];
para tree[2 * R];
int tree2[2 * R];
queue<int> q;

void push(int v) {
	if (tree2[v] == 0) return;
	tree[2 * v].first -= tree2[v];
	tree2[2 * v] += tree2[v];
	tree[2 * v + 1].first -= tree2[v];
	tree2[2 * v + 1] += tree2[v];
	tree2[v] = 0;
}

void odejmij(int pocz, int kon, int wart, int l = POCZ, int r = KON, int v = 1) {
	if (r < pocz || kon < l) return;
	if (pocz <= l && r <= kon) {
		tree[v].first -= wart;
		tree2[v] += wart;
		return;
	}
	push(v);
	int srodek = (l + r) / 2;
	odejmij(pocz, kon, wart, l, srodek, 2 * v);
	odejmij(pocz, kon, wart, srodek + 1, r, 2 * v + 1);
	tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

void ustaw(int pozycja, int wart, int l = POCZ, int r = KON, int v = 1) {
	if (r < pozycja || pozycja < l) return;
	if (l == pozycja && pozycja == r) {
		tree[v].first = wart;
		return;
	}
	push(v);
	int srodek = (l + r) / 2;
	ustaw(pozycja, wart, l, srodek, 2 * v);
	ustaw(pozycja, wart, srodek + 1, r, 2 * v + 1);
	tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

void zmiejsz(int pocz, int kon, int indeks) {
	odejmij(R + pocz, R + kon, 1);
	
	while (tree[1].first == 0) {
		wynik[tree[1].second - R] = indeks;
		ustaw(tree[1].second, INT_MAX);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = R; i < 2 * R; i++) {
		tree[i] = {n - 1, i};
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		krawedzie[i] = {a, b};
		graf[a].push_back(b);
		poziom[b]++;
	}
	
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	int indeks = 0;
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		numer[v] = (++indeks);
		
		for (int u : graf[v]) {
			poziom[u]--;
			if (poziom[u] == 0) {
				q.push(u);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		nast[i] = n + 1;
		pop[i] = 0;
		wynik[i] = -1;
	}
	
	for (int i = 1; i <= m; i++) {
		int a = numer[krawedzie[i].first];
		int b = numer[krawedzie[i].second];
		
		if (b < nast[a]) {
			zmiejsz(b, nast[a] - 1, i);
			nast[a] = b;
		}
		
		if (a > pop[b]) {
			zmiejsz(pop[b] + 1, a, i);
			pop[b] = a;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << wynik[numer[i]] << " ";
	}

	return 0;
}

