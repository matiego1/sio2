#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> para;

struct Zapytanie {
	int cel, dystans, indeks;
};
Zapytanie make_zapytanie(int cel, int dystans, int indeks) {
	return {cel, dystans, indeks};
}

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 5000;
const int MAX_K = 1000 * 1000;

vector<int> graf[2 * MAX + 1];
int odleg[2 * MAX + 1];
vector<Zapytanie> zapytania[MAX + 1];
bool odpowiedzi[MAX_K + 1];

void bfs(int n, int pocz) {
	for (int i = 1; i <= 2 * n; i++) {
		odleg[i] = INF;
	}
	
	queue<int> q;
	q.push(pocz);
	odleg[pocz] = 0;
	
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		
		for (int u : graf[v]) {
			if (odleg[u] == INF) {
				odleg[u] = odleg[v] + 1;
				q.push(u);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b + n);
		graf[b + n].push_back(a);
		
		graf[a + n].push_back(b);
		graf[b].push_back(a + n);
	}
	
	for (int i = 1; i <= k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		
		zapytania[a].push_back(make_zapytanie(b, c, i));
	}
	
	for (int i = 1; i <= n; i++) {
		if (zapytania[i].empty() || graf[i].empty()) continue;
		
		bfs(n, i);
		
		for (Zapytanie zapyt : zapytania[i]) {
			if (zapyt.dystans % 2 != 0) {
				zapyt.cel += n;
			}
			
			if (zapyt.dystans >= odleg[zapyt.cel]) {
				odpowiedzi[zapyt.indeks] = true;
			}
		}
	}
	
	for (int i = 1; i <= k; i++) {
		cout << (odpowiedzi[i] ? "TAK\n" : "NIE\n");
	}

	return 0;
}
