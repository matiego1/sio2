#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Node {
	int wynik, pref, suff, rozmiar = 1;
};

const int MAX = 200 * 1000;
const int R = (1 << 20);
para wej[MAX + 1];
set<int> zbior;
map<int, int> mapa; // dzien -> indeks w drzewie
int liscie[3 * MAX + 1];
Node tree[2 * R];

void aktualizuj(int i) {
	tree[i].wynik = max(tree[2 * i].suff + tree[2 * i + 1].pref, max(tree[2 * i].wynik, tree[2 * i + 1].wynik));
	if (tree[2 * i].pref >= tree[2 * i].rozmiar) {
		tree[i].pref = tree[2 * i].rozmiar + tree[2 * i + 1].pref;
	} else {
		tree[i].pref = tree[2 * i].pref;
	}
	if (tree[2 * i + 1].suff >= tree[2 * i + 1].rozmiar) {
		tree[i].suff = tree[2 * i + 1].rozmiar + tree[2 * i].suff;
	} else {
		tree[i].suff = tree[2 * i + 1].suff;
	}
}

void zmien(int i, int wart) {
	liscie[i] += wart;
	if (wart == 1 && liscie[i] == 1) {
		i += R;
		tree[i].wynik = 1;
		tree[i].pref = 1;
		tree[i].suff = 1;
	} else if (wart == -1 && liscie[i] == 0) {
		i += R;
		tree[i].wynik = 0;
		tree[i].pref = 0;
		tree[i].suff = 0;
	} else return;
	while (i > 1) {
		i /= 2;
		aktualizuj(i);
	}
}

int rozwiaz() {
	int n, m;
	cin >> n >> m;
	
	zbior.clear();
	for (int i = 1; i <= n; i++) {
		cin >> wej[i].first;
		wej[i].second = m - (wej[i].first % m);

		int dzien = wej[i].first / m;
		zbior.insert(dzien);
		zbior.insert(dzien + 1);
		zbior.insert(dzien + 2);
	}
	
	int indeks = 0;
	for (int dzien : zbior) {
		mapa[dzien] = ++indeks;
		liscie[indeks] = 0;
	}
	
	for (int i = 1; i <= n; i++) {
		liscie[mapa[wej[i].first / m]]++;
	}
	
	for (int i = 1; i <= indeks; i++) {
		if (liscie[i] == 0) {
			tree[R + i] = {0, 0, 0, 1};
		} else {
			tree[R + i] = {1, 1, 1, 1};
		}
	}
	for (int i = R + indeks + 1; i < 2 * R; i++) {
		tree[i] = {0, 0, 0, 1};
	}
	for (int i = R - 1; i >= 1; i--) {
		aktualizuj(i);
	}
	
	sort(wej + 1, wej + 1 + n, [](para& p1, para& p2) { return p1.second < p2.second; });
	
	int wynik = tree[1].wynik;
	for (int i = 1; i <= n; i++) {
		if (wej[i].second >= m) continue;
		
		zmien(mapa[wej[i].first / m], -1);
		zmien(mapa[wej[i].first / m + 1], 1);
		
		if (i < n && wej[i + 1].second == wej[i].second) continue;
		wynik = max(wynik, tree[1].wynik);
	}

	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i].rozmiar = tree[2 * i].rozmiar + tree[2 * i + 1].rozmiar;
	}

	int t;
	cin >> t;
	while (t--) {
		cout << rozwiaz() << "\n";
	}

	return 0;
}

