#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
const int R = (1 << 19);
vector<para> tree[2 * R];
vector<int> czujniki[MAX + 1];
int rozmiar[MAX + 1];
int ilosc[2 * R];
ll wynik = 0;
int n;

void zbuduj(int l = 0, int r = n - 1, int v = 1) {
	ilosc[v] = r - l + 1;
	tree[v].clear();
	
	if (l == r) return;
	
	int srodek = (l + r) / 2;
	zbuduj(l, srodek, 2 * v);
	zbuduj(srodek + 1, r, 2 * v + 1);
}

void reset(int x) {
	for (para p : tree[x]) {
		if (rozmiar[p.first] == 1) wynik -= (ll) p.first * p.first;
		rozmiar[p.first] -= czujniki[p.first][p.second];
		
		czujniki[p.first][p.second] = ilosc[x];
		
		rozmiar[p.first] += czujniki[p.first][p.second];
		if (rozmiar[p.first] == 1) wynik += (ll) p.first * p.first;
	}
}

void dodaj(int pocz, int kon, int x, int l = 0, int r = n - 1, int v = 1) {
	if (pocz <= l && r <= kon) {
		czujniki[x].push_back(r - l + 1);
		tree[v].push_back({x, (int) czujniki[x].size() - 1});
		return;
	}
	
	int srodek = (l + r) / 2;
	if (pocz <= srodek) dodaj(pocz, kon, x, l, srodek, 2 * v);
	if (kon > srodek) dodaj(pocz, kon, x, srodek + 1, r, 2 * v + 1);
}

void zmien(int x, int l = 0, int r = n - 1, int v = 1) {
	if (l == r) {
		ilosc[v] = 0;
		reset(v);
		return;
	}
	
	int srodek = (l + r) / 2;
	if (x <= srodek) {
		zmien(x, l, srodek, 2 * v);
	} else {
		zmien(x, srodek + 1, r, 2 * v + 1);
	}
	
	ilosc[v] = ilosc[2 * v] + ilosc[2 * v + 1];
	if (ilosc[v] == 0 || ilosc[v] == 1) reset(v);
}

void rozwiaz() {
	int m;
	cin >> n >> m;
	
	wynik = 0;
	zbuduj();
	
	for (int i = 1; i <= m; i++) {
		int pocz, kon;
		cin >> pocz >> kon;
		
		czujniki[i].clear();
		rozmiar[i] = kon - pocz + 1;
		dodaj(pocz, kon, i);
		
		if (rozmiar[i] == 1) wynik += (ll) i * i;
	}
	
	cout << wynik << " ";
	
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		x = (int) ((wynik + x) % n);

		zmien(x);
		
		cout << wynik << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		rozwiaz();
	}

	return 0;
}

