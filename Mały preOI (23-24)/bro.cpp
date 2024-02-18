#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> para;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 5000;
const int K = 850;
vector<int> graf[MAX + 1];

int odleg[MAX + 1][MAX + 1];
int sila[MAX + 1];
vector<para> maszty;
priority_queue<para> kolejka;

void bfs(int n, int pocz) {
	for (int i = 1; i <= n; i++) {
		odleg[pocz][i] = INF;
	}
	
	queue<para> kolejka;
	kolejka.push({pocz, 0});
	odleg[pocz][pocz] = 0;
	while (!kolejka.empty()) {
		para v = kolejka.front();
		kolejka.pop();
		
		for (int u : graf[v.first]) {
			if (odleg[pocz][u] == INF) {
				odleg[pocz][u] = v.second + 1;
				kolejka.push({u, odleg[pocz][u]});
			}
		}
	}	
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		bfs(n, i);
	}
	
	int q;
	scanf("%d", &q);
	
	while (q--) {
		char typ;
		scanf(" %c", &typ);
		int v;
		scanf("%d", &v);
		if (typ == '+') {
			int s;
			scanf("%d", &s);
			
			maszty.push_back({v, s});
			kolejka.push({s, v});
		} else {
			int wynik = sila[v];
			for (para maszt : maszty) {
				wynik = max(wynik, maszt.second - odleg[maszt.first][v]);
			}
			printf("%d\n", wynik);
		}
		
		if (maszty.size() >= K) {
			maszty.clear();
			while (!kolejka.empty()) {
				para akt = kolejka.top();
				kolejka.pop();
				
				if (sila[akt.second] >= akt.first) continue;
				sila[akt.second] = akt.first;
				
				akt.first--;
				if (akt.first <= 0) continue;
				
				for (int u : graf[akt.second]) {
					kolejka.push({akt.first, u});
				}
			}
		}
	}

	return 0;
}
