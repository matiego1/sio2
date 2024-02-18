#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct Krawedz {
	int v, u, waga;
};
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX_N = 5000;
const int MAX_M = 10 * 1000;

int n, m;
Krawedz krawedzie[MAX_M + 1];
ll odleg[MAX_N + 1];
int poprzednik[MAX_N + 1];
bool odwie[MAX_N + 1];
vector<int> wynik;

bool jest_cykl(int pocz) {
	for (int i = 1; i <= n; i++) {
		odleg[i] = INF;
		poprzednik[i] = -1;
	}
	
	odleg[pocz] = 0;
	int ost = -1;
	for (int i = 1; i <= n; i++) {
		ost = -1;
		for (int j = 1; j <= m; j++) {
			if (odleg[krawedzie[j].v] < INF && odleg[krawedzie[j].u] > odleg[krawedzie[j].v] + krawedzie[j].waga) {
				odleg[krawedzie[j].u] = max(-INF, odleg[krawedzie[j].v] + krawedzie[j].waga);
				poprzednik[krawedzie[j].u] = j;
				ost = krawedzie[j].u;
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (odleg[i] < INF) {
			odwie[i] = true;
		}
	}
	
	if (ost == -1) return false;
	
	cout << "TAK\n";
	
	for (int i = 1; i <= n; i++) {
		ost = krawedzie[poprzednik[ost]].v;
	}
	
	for (int akt = ost; wynik.size() <= 1 || akt != ost; akt = krawedzie[poprzednik[akt]].v) {
		wynik.push_back(poprzednik[akt]);
	}
	
	cout << wynik.size() << " ";
	
	for (int i = wynik.size() - 1; i >= 0; i--) {
		cout << wynik[i] << " ";
	}
	
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, c};
	}
	
	for (int i = 1; i <= n; i++) {
		if (!odwie[i]) {
			if (jest_cykl(i)) return 0;
		}
	}
	cout << "NIE";

	return 0;
}
