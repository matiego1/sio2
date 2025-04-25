#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int K = 5;
const int R = (1 << 20);
int tree[2 * R][K];
int tree2[2 * R][K];
int pom[2][K];

void push(int v) {
	for (int i = 0; i < K; i++) {
		pom[0][i] = tree[2 * v][i];
		pom[1][i] = tree[2 * v + 1][i];
	}

	for (int i = 0; i < K; i++) {
		tree2[2 * v][i] = tree2[v][tree2[2 * v][i]];
		tree[2 * v][i] -= pom[0][i];
		tree[2 * v][tree2[v][i]] += pom[0][i];
	   
		tree2[2 * v + 1][i] = tree2[v][tree2[2 * v + 1][i]];
		tree[2 * v + 1][i] -= pom[1][i];
		tree[2 * v + 1][tree2[v][i]] += pom[1][i];
	}
	
	for (int i = 0; i < K; i++) {
		tree2[v][i] = i;
	}
}

void ustaw(int pocz, int kon, int a, int b, int l, int r, int v) {
	if (r < pocz || kon < l) return;
	if (pocz <= l && r <= kon) {
		for (int i = 0; i < K; i++) {
			if (tree2[v][i] == a) {
				tree2[v][i] = b;
			}
		}
		
		tree[v][b] += tree[v][a];
		tree[v][a] = 0;
		return;
	}
	
	push(v);
	
	int srodek = (l + r) / 2;
	ustaw(pocz, kon, a, b, l, srodek, 2 * v);
	ustaw(pocz, kon, a, b, srodek + 1, r, 2 * v + 1);
	
	for (int i = 0; i < K; i++) {
		tree[v][i] = tree[2 * v][i] + tree[2 * v + 1][i];
	}
}

int query(int a, int p, int akt, int l, int r, int v) {
	if (l == r) return l;

	push(v);
	
	int srodek = (l + r) / 2;
	if (akt + tree[2 * v][a] < p) {
		return query(a, p, akt + tree[2 * v][a], srodek + 1, r, 2 * v + 1);
	} else {
		return query(a, p, akt, l, srodek, 2 * v);
	}
}

int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(' '), m = wczytaj('\n');
	
	for (int i = 1; i <= n; i++) {
		char c = getchar();
		tree[R + i][c - 'a'] = 1;
	}
	getchar();

	for (int i = R - 1; i >= 1; i--) {
		for (int j = 0; j < K; j++) {
			tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
		}
	}

	for (int i = 1; i < 2 * R; i++) {
		for (int j = 0; j < K; j++) {
			tree2[i][j] = j;
		}
	}

	while (m--) {
		int p = wczytaj(' ');
		char a = getchar();
		getchar();
		char b = getchar();
		getchar();

		if (a == b) continue;

		int kon = query(a - 'a', p, 0, 1, R, 1);
		ustaw(1, kon, a - 'a', b - 'a', 1, R, 1);
	}

	for (int i = 1; i < R; i++) {
		push(i);
	}
	
	for (int i = R + 1; i <= R + n; i++) {
		for (int j = 0; j < K; j++) {
			if (tree[i][j]) {
				putchar(j + 'a');
			}
		}
	}

	return 0;
}
