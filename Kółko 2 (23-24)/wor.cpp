#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> para;

const int MAX = 2000;
bool czy_wolne[MAX + 2][MAX + 2];
bool odwie[MAX + 1][MAX + 1];
queue<para> q;
int n, m;

bool sprawdz(int poziom) {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			odwie[i][j] = false;
		}
	}	
	
	int ostatni = n - poziom;
	
	while (!q.empty()) q.pop();
	for (int i = 1; i <= n; i++) {
		if (czy_wolne[1][i]) {
			q.push({1, i});
		}
	}
	
	while (!q.empty()) {
		para akt = q.front();
		int x = akt.first, y = akt.second;
		q.pop();
		
		if (odwie[x][y]) continue;
		odwie[x][y] = true;
		
		int posX[4] = {1, 0, -1, 0};
		int posY[4] = {0, 1, 0, -1};
		for (int i = 0; i < 4; i++) {
			if (!czy_wolne[x + posX[i]][y + posY[i]]) continue;
			if (y + posY[i] > ostatni) continue;
			if (odwie[x + posX[i]][y + posY[i]]) continue;
			if (x + posX[i] == m) return true;
			q.push({x + posX[i], y + posY[i]});
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			char c;
			cin >> c;
			czy_wolne[x][y] = (c == '.');
		}
	}
	
	if (!sprawdz(0)) {
		cout << "NIE";
		return 0;
	}
	
	int pocz = 0, kon = n;
	while (pocz < kon) {
		int srodek = (pocz + kon + 1) / 2;
		if (sprawdz(srodek)) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
		}
	}
	cout << pocz;

	return 0;
}

