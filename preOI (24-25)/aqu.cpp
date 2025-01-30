#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Grupa {
	int indeks, rozmiar, c;
};

const int MAX = 200 * 1000;
const int MAX_Z = 200 * 1000;
const int R = (1 << 18);
bool aktywna[MAX + 1];
int rozmiar[MAX + 1];
queue<int> kolejka[MAX_Z + 1];
para tree[2 * R];

vector<para> wynik;

void ustaw_pierwszy(int i, int wart) {
	i += R;
	tree[i].first = wart;
	while (i > 1) {
		i /= 2;
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
}

para query_pierwszy(int kon) {
	int pocz = R;
	kon += R;
	para mini = min(tree[pocz], tree[kon]);
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			mini = min(mini, tree[pocz + 1]);
		}
		if (kon % 2 == 1) {
			mini = min(mini, tree[kon - 1]);
		}
		pocz /= 2;
		kon /= 2;
	}
	return mini;
}

void pushuj(int z, int indeks) {
	if (kolejka[z].empty()) {
		ustaw_pierwszy(z, indeks);
	}
	kolejka[z].push(indeks);
}
void popuj(int z) {
	kolejka[z].pop();
	if (kolejka[z].empty()) {
		ustaw_pierwszy(z, INT_MAX);
	} else {
		ustaw_pierwszy(z, kolejka[z].front());
	}
}

para znajdz_mini(int m) {
	para mini = query_pierwszy(m);
	while (mini.first != INT_MAX && !aktywna[mini.first]) {
		popuj(mini.second);
		mini = query_pierwszy(m);
	}
	return mini;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for (int i = R; i < 2 * R; i++) {
		tree[i] = {INT_MAX, i - R};
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	} 

	int q;
	cin >> q;
	
	int indeks = 0, wziety_indeks = 0;
	while (q--) {
		char typ;
		cin >> typ;
		if (typ == 'D') {
			int z, c;
			cin >> z >> c;
			
			indeks++;
			aktywna[indeks] = true;
			rozmiar[indeks] = z;
			
			if (c == 0) {
				pushuj(z, indeks);
			} else {
				pushuj(0, indeks);
			}
		} else if (typ == 'R') {
			int i;
			cin >> i;
			aktywna[i] = false;
		} else {
			ll m;
			cin >> m;
			
			while (m > MAX_Z) {
				while (wziety_indeks <= indeks && !aktywna[wziety_indeks]) wziety_indeks++;
				if (wziety_indeks > indeks) break;
				
				m -= rozmiar[wziety_indeks];
				aktywna[wziety_indeks] = false;
				wynik.push_back({wziety_indeks, rozmiar[wziety_indeks]});
			}
			
			if (m > MAX_Z) {
				cout << wynik.size() << "\n";
				for (para p : wynik) {
					cout << p.first << " " << p.second << "\n";
				}
				wynik.clear();
				continue;
			}
			
			while (m) {
				para p = znajdz_mini(min((int) m, MAX_Z));
				int mini = p.first, mini_z = p.second;
				if (mini == INT_MAX) break;
				
				if (rozmiar[mini] <= m) {
					popuj(mini_z);
					aktywna[mini] = false;
					m -= rozmiar[mini];
					wynik.push_back({mini, rozmiar[mini]});
				} else {
					wynik.push_back({mini, m});
					rozmiar[mini] -= (int) m;
					m = 0;
				}
			}
			
			cout << wynik.size() << "\n";
			for (para p : wynik) {
				cout << p.first << " " << p.second << "\n";
			}
			wynik.clear();
		}
	}

	return 0;
}
