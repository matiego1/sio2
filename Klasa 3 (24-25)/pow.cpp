#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int INF = 1000 * 1000 * 1000;
const int MAX = 1000;
int wej[MAX + 2][MAX + 2];
vector<para> wys[MAX + 1];
int kra[MAX * MAX + 1];
bool czy_pompa[MAX * MAX + 1];

int indeks(int x, int y) {
	return (y - 1) * MAX + x;
}

int delta_x[4] = {1, 0, -1, 0};
int delta_y[4] = {0, 1, 0, -1};

int findd(int x) {
	if (kra[x] == x) return x;
	return (kra[x] = findd(kra[x]));
}

bool unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return false;
	kra[a] = b;
	czy_pompa[b] = (czy_pompa[b] || czy_pompa[a]);
	return true;
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int m, n;
	cin >> m >> n;
	
	for (int i = 1; i <= MAX * MAX; i++) kra[i] = i;
	for (int x = 1; x <= n; x++) {
		wej[x][0] = INF;
		wej[x][m + 1] = INF;
	}
	for (int y = 1; y <= m; y++) {
		wej[0][y] = INF;
		wej[n + 1][y] = INF;
	}

	for (int y = 1; y <= m; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> wej[x][y];
			wys[abs(wej[x][y])].push_back({x, y});
		}
	}
	
	int wynik = 0;
	for (int h = 1; h <= MAX; h++) {
		for (para pole : wys[h]) {
			int akt = indeks(pole.first, pole.second);
			for (int i = 0; i < 4; i++) {
				int nowe_x = pole.first + delta_x[i];
				int nowe_y = pole.second + delta_y[i];
				if (abs(wej[nowe_x][nowe_y]) > abs(wej[pole.first][pole.second])) continue;
				if (unionn(akt, indeks(nowe_x, nowe_y))) {
				}
			}
		}
		for (para pole : wys[h]) {
			int grupa = findd(indeks(pole.first, pole.second));
			if (czy_pompa[grupa]) continue;
			if (wej[pole.first][pole.second] < 0) continue;
			czy_pompa[grupa] = true;
			wynik++;
		}
	}
	cout << wynik;

	return 0;
}


