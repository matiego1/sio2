#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
int poziom[MAX + 1];
int wynik[MAX + 1];
int indeks = 0;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b);
		poziom[b]++;
	}
	
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	while (!q.empty()) {
		int akt = q.front();
		q.pop();
		
		wynik[indeks++] = akt;
		
		for (int u : graf[akt]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
	}
	
	if (indeks != n) {
		cout << "NIE";
	} else {
		cout << "TAK\n";
		for (int i = 0; i < indeks; i++) {
			cout << wynik[i] << " ";
		}
	}

	return 0;
}