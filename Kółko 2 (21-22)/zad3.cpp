#include <iostream>
#include <vector>
using namespace std;

struct Krawedz {
	int v, u, waga;
};
const int INF = 2 * 1000 * 1000 * 1000;
const int MAX_N = 1000;
const int MAX_M = 10 * 1000;
int n, m;
Krawedz krawedzie[MAX_M + 1];
int odleg[MAX_N + 1];
int poprzednik[MAX_N + 1];

void rozwiaz(int pocz, int kon) {
	for (int i = 1; i <= n; i++) {
		odleg[i] = INF;
		poprzednik[i] = -1;
	}
	
	odleg[pocz] = 0;
	poprzednik[pocz] = pocz;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			if (odleg[krawedzie[j].v] != INF && odleg[krawedzie[j].u] > odleg[krawedzie[j].v] + krawedzie[j].waga) {
				odleg[krawedzie[j].u] = odleg[krawedzie[j].v] + krawedzie[j].waga;
				poprzednik[krawedzie[j].u] = krawedzie[j].v;
			}
		}
	}
	
	if (odleg[kon] == INF) {
		cout << "NIE\n";
		return;
	}
	
	cout << odleg[kon] << " ";
	
	vector<int> wynik;
	wynik.push_back(kon);
	while (poprzednik[kon] != kon) {
		kon = poprzednik[kon];
		wynik.push_back(kon);
	}
	
	cout << wynik.size() << " ";
	for (int i = wynik.size() - 1; i >= 0; i--) {
		cout << wynik[i] << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int q;
	cin >> n >> m >> q;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, c};
	}
	
	while (q--)  {
		int a, b;
		cin >> a >> b;
		rozwiaz(a, b);
	}

	return 0;
}