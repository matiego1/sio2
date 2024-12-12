#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
const int R = (1 << 19);
vector<int> graf[MAX + 1];
int rozmiar[MAX + 1];
para odleg[MAX + 1];
int ile[2][MAX + 1];
int tree[2][2][2 * R];
int A[MAX + 1];
int B[MAX + 1];

void dfs_rozmiar(int v, int p) {
	rozmiar[v] = 1;
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs_rozmiar(u, v);
		rozmiar[v] += rozmiar[u];
	}
}

int dfs_centroid(int v, int p, int n) {
	for (int u : graf[v]) {
		if (u == p) continue;
		if (rozmiar[u] > n / 2) {
			return dfs_centroid(u, v, n);
		}
	}
	return v;
}

void dodaj(int zbior, int centroid, int indeks, int wart) {
	indeks += R;
	tree[zbior][centroid][indeks] += wart;
	while (indeks > 1) {
		indeks /= 2;
		tree[zbior][centroid][indeks] = tree[zbior][centroid][2 * indeks] + tree[zbior][centroid][2 * indeks + 1];
	}
}

int query(int zbior, int centroid, int pocz, int kon) {
	if (kon < pocz) return 0;
	pocz += R;
	kon += R;
	int wynik = tree[zbior][centroid][pocz];
	if (pocz != kon) wynik += tree[zbior][centroid][kon];
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			wynik += tree[zbior][centroid][pocz + 1];
		}
		if (kon % 2 == 1) {
			wynik += tree[zbior][centroid][kon - 1];
		}
		pocz /= 2;
		kon /= 2;
	}
	return wynik;
}

void dfs_odleg(int v, int p, int gleb, int pierwszy) {
	if (pierwszy) {
		odleg[v] = {gleb, 0};
	} else if (gleb < odleg[v].first) {
		odleg[v] = {gleb, 1};
	}
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs_odleg(u, v, gleb + 1, pierwszy);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	dfs_rozmiar(1, 1);
	int centroid1 = dfs_centroid(1, 1, rozmiar[1]);
	dfs_rozmiar(centroid1, centroid1);
	int centroid2 = 0;
	for (int u : graf[centroid1]) {
		if (rozmiar[centroid1] - rozmiar[u] <= n / 2) {
			centroid2 = u;
			break;
		}
	}
	
	dfs_odleg(centroid1, centroid1, 0, true);
	dfs_odleg(centroid2, centroid2, 0, false);

	int na, nb, q;
	cin >> na >> nb >> q;
	
	for (int i = 1; i <= na; i++) {
		cin >> A[i];
		ile[0][A[i]]++;
		dodaj(0, odleg[A[i]].second, odleg[A[i]].first, 1);
	}
	for (int i = 1; i <= nb; i++) {
		cin >> B[i];
		ile[1][B[i]]++;
		dodaj(1, odleg[B[i]].second, odleg[B[i]].first, 1);
	}
	
	ll wynik = 0;
	for (int i = 1; i <= na; i++) {
		para p = odleg[A[i]];
		if (ile[1][A[i]]) dodaj(1, p.second, p.first, -1);
		wynik += query(1, p.second, p.first, n);
		wynik += query(1, 1 ^ p.second, p.first + 1, n);
		if (ile[1][A[i]]) dodaj(1, p.second, p.first, 1);
	}
	cout << wynik << "\n";
	
	while (q--) {
		char z, t;
		int v;
		cin >> z >> t >> v;
		
		int grupa = (z == 'A' ? 0 : 1);
		int operacja = (t == '+' ? 1 : -1);
		
		dodaj(grupa, odleg[v].second, odleg[v].first, operacja);
		ile[grupa][v] += operacja;
		
		grupa ^= 1;
		para p = odleg[v];
		if (ile[grupa][v]) dodaj(grupa, p.second, p.first, -1);
		if (z == 'A') {
			wynik += query(1, p.second, p.first, n) * operacja;
			wynik += query(1, 1 ^ p.second, p.first + 1, n) * operacja;
		} else {
			wynik += query(0, p.second, 0, p.first) * operacja;
			wynik += query(0, 1 ^ p.second, 0, p.first - 1) * operacja;
		}
		if (ile[grupa][v]) dodaj(grupa, p.second, p.first, 1);
		
		cout << wynik << "\n";
	}
	
	return 0;
}
