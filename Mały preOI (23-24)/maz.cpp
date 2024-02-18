#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> para;

struct Punkt {
	int x, y;
};
Punkt make_punkt(int x, int y) {
	return {x, y};
}

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 500;
int n, k;
Punkt start, meta;
int wej[MAX + 1][MAX + 1];
int oplata[MAX + 1][MAX + 1];
int odleg[MAX + 1][MAX + 1];

bool sprawdz(int karnet) {
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			odleg[x][y] = INF;
			oplata[x][y] = (wej[x][y] > karnet);
		}
	}
	
	deque<Punkt> q;
	odleg[start.x][start.y] = oplata[start.x][start.y];
	q.push_front(start);
	
	while (!q.empty()) {
		Punkt akt = q.front();
		q.pop_front();
		
		int wart_x[4] = {1, 0, -1, 0}; 
		int wart_y[4] = {0, 1, 0, -1};
		for (int i = 0; i < 4; i++) {
			Punkt v = akt;
			v.x += wart_x[i];
			v.y += wart_y[i];
			
			if (v.x <= 0 || v.x > n) continue;
			if (v.y <= 0 || v.y > n) continue;
			
			if (odleg[v.x][v.y] != INF) continue;
			
			odleg[v.x][v.y] = odleg[akt.x][akt.y] + oplata[v.x][v.y];
			
			if (oplata[v.x][v.y]) {
				q.push_back(make_punkt(v.x, v.y));
			} else {
				q.push_front(make_punkt(v.x, v.y));
			}
		}
	}
	
	return odleg[meta.x][meta.y] <= k;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	cin >> start.x >> start.y >> meta.x >> meta.y;
	
	int maks = 0;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> wej[y][x];
			maks = max(maks, wej[y][x]);
		}
	}
	
	int pocz = 0, kon = maks;
	while (pocz < kon) {
		int srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	
	if (pocz == 0) {
		cout << "TRIV";
	} else {
		cout << pocz;
	}

	return 0;
}

