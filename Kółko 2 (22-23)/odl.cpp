#include <iostream>
#include <vector>
using namespace std;
struct Krawedz {
	int u, v, waga;
};

const int MAX = 500;
const int INF = 1000 * 1000 * 1000;
int odleg[MAX + 1][MAX + 1];
Krawedz krawedzie[MAX * MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				odleg[i][j] = 0;
			} else {
				odleg[i][j] = INF;
			}
		}
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, c};
		if (a != b) odleg[a][b] = c;
	}
	
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (odleg[i][k] < INF && odleg[k][j] < INF && odleg[i][j] > odleg[i][k] + odleg[k][j]) {
					odleg[i][j] = max(-INF, odleg[i][k] + odleg[k][j]);
				}
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (odleg[i][k] < INF && odleg[k][k] < 0 && odleg[k][j] < INF) {
					odleg[i][j] = -INF;
				}
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (odleg[i][j] == -INF) {
				cout << "-oo ";
			} else if (odleg[i][j] == INF) {
				cout << "* ";
			} else {
				cout << odleg[i][j] << " ";
			}
		}
		cout << "\n";
	}

	return 0;
}

