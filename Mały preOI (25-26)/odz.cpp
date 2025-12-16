#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_T = 1000 * 1000;
const int MAX = 300 * 1000;
const int R = (1 << 19);
int wej[MAX + 1];
int maks[2 * R];
int mini[2 * R];
int tree[2 * R];
set<int> pozycje[MAX_T + 1];

void ustaw(int v, int wart) {
	v += R;
	
	maks[v] = wart;
	mini[v] = wart;
	
	while (v > 1) {
		v /= 2;
		maks[v] = max(maks[2 * v], maks[2 * v + 1]);
		mini[v] = min(mini[2 * v], mini[2 * v + 1]);
	}
}

void ustaw_poz(int v, int wart) {
	v += R;
	tree[v] = wart;
	
	while (v > 1) {
		v /= 2;
		tree[v] = max(tree[2 * v], tree[2 * v + 1]);
	}
}

para query(int pocz, int kon) {
	pocz += R;
	kon += R;
	
	int akt_mini = min(mini[pocz], mini[kon]);
	int akt_maks = max(maks[pocz], maks[kon]);
	int akt = max(tree[pocz], tree[kon]);
	
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			akt_mini = min(akt_mini, mini[pocz + 1]);
			akt_maks = max(akt_maks, maks[pocz + 1]);
			akt = max(akt, tree[pocz + 1]);
		}
		if (kon % 2 == 1) {
			akt_mini = min(akt_mini, mini[kon - 1]);
			akt_maks = max(akt_maks, maks[kon - 1]);
			akt = max(akt, tree[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	
	return {akt_maks - akt_mini + 1, akt};
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), t = wczytaj(), q = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		wej[i] = wczytaj();
		maks[i + R] = wej[i];
		mini[i + R] = wej[i];
		pozycje[wej[i]].insert(i);
	}
	
	for (int i = 1; i <= n; i++) {
		auto it = pozycje[wej[i]].lower_bound(i);
		if (it != pozycje[wej[i]].begin()) {
			it--;
			tree[i + R] = *it;
		}
	}
	
	for (int i = R - 1; i >= 1; i--) {
		maks[i] = max(maks[2 * i], maks[2 * i + 1]);
		mini[i] = min(mini[2 * i], mini[2 * i + 1]);
		tree[i] = max(tree[2 * i], tree[2 * i + 1]);
	}
	
	while (q--) {
		int typ = wczytaj();
		
		if (typ == 1) {
			int l = wczytaj(), r = wczytaj();
			
			para x = query(l, r);
			if (x.first == r - l + 1 && x.second < l) {
				putchar('T');putchar('A');putchar('K');putchar('\n');
			} else {
				putchar('N');putchar('I');putchar('E');putchar('\n');
			}
		} else {
			int indeks = wczytaj(), nowa = wczytaj();
			int stara = maks[indeks + R];
			
			ustaw_poz(indeks, 0);
			
			pozycje[stara].erase(indeks);
			auto it = pozycje[stara].lower_bound(indeks);
			if (it != pozycje[stara].end()) {
				int a = *it;
				int b = 0;
				if (it != pozycje[stara].begin()) {
					it--;
					b = *it;
				}
				ustaw_poz(a, b);
			}
			
			pozycje[nowa].insert(indeks);
			it = pozycje[nowa].upper_bound(indeks);
			if (it != pozycje[nowa].end()) {
				ustaw_poz(*it, indeks);
			}
			it = pozycje[nowa].lower_bound(indeks);
			if (it != pozycje[nowa].begin()) {
				it--;
				ustaw_poz(indeks, *it);
			}
			
			ustaw(indeks, nowa);
		}
	}

	return 0;
}
