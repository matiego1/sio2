#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
struct Element {
	int x, y, maska;
};

const int MAX = 200;
const int K = 8;
const int INF = 2000 * 1000 * 1000;

int n, m;
char wej[MAX + 1][MAX + 1];
bool odwie[MAX + 1][MAX + 1][1 << 8];
int odleg[MAX + 1][MAX + 1][1 << 8];
const int delta_x[4] = {1, 0, -1, 0};
const int delta_y[4] = {0, 1, 0, -1};

bool czy_klucz(int maska, char c) {
	return maska & (1 << (c - ('A' <= c && c <= 'H' ? 'A' : 'a')));
}

void dodaj_nowe(int x, int y, int maska, int koszt, queue<Element>& q) {
	for (int i = 0; i < 4; i++) {
		int nowe_x = x + delta_x[i];
		int nowe_y = y + delta_y[i];
		
		if (nowe_x < 1 || nowe_x > m) continue;
		if (nowe_y < 1 || nowe_y > n) continue;
		
		if (wej[nowe_x][nowe_y] == '#') continue;
		if ('A' <= wej[nowe_x][nowe_y] && wej[nowe_x][nowe_y] <= 'H' && !czy_klucz(maska, wej[nowe_x][nowe_y])) continue;

		if (odwie[nowe_x][nowe_y][maska]) continue;
		odwie[nowe_x][nowe_y][maska] = true;

		odleg[nowe_x][nowe_y][maska] = min(odleg[nowe_x][nowe_y][maska], odleg[x][y][maska] + koszt);
		
		q.push({nowe_x, nowe_y, maska});
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	
	para start;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			cin >> wej[x][y];
			if (wej[x][y] == 'S') start = {x, y};
			for (int i = 0; i < (1 << K); i++) odleg[x][y][i] = INF;
		}
	}
	
	queue<Element> q;
	q.push({start.first, start.second, 0});
	odwie[start.first][start.second][0] = true;
	odleg[start.first][start.second][0] = 0;
	
	while (q.size()) {
		Element e = q.front();
		q.pop();
		
		if (wej[e.x][e.y] == 'W') {
			int wynik = INF;
			for (int i = 1; i < (1 << K); i++) {
				wynik = min(wynik, odleg[e.x][e.y][i]);
			}
			cout << wynik;
			return 0;
		}
		
		dodaj_nowe(e.x, e.y, e.maska, 1, q);
		
		if ('a' <= wej[e.x][e.y] && wej[e.x][e.y] <= 'h' && !czy_klucz(e.maska, wej[e.x][e.y])) {
			int nowa_maska = e.maska | (1 << (wej[e.x][e.y] - 'a'));
			odleg[e.x][e.y][nowa_maska] = min(odleg[e.x][e.y][nowa_maska], odleg[e.x][e.y][e.maska]);
			dodaj_nowe(e.x, e.y, nowa_maska, 2, q);
		}
	}
	
	for (int i = 1; i <= 63; i++) {
		cout << "ZELAZKO\n";
	}

	return 0;
}