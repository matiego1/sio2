#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
int poziom[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
	}
	
	for (int i = 1; i <= n; i++) {
		for (int u : graf[i]) {
			poziom[u]++;
		}
	}
	
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		} 
	}
	
	vector<int> wynik;
	
	while (!q.empty()) {
		int akt = q.top();
		q.pop();
		wynik.push_back(akt);
		for (int u : graf[akt]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
	}
	
	if (wynik.size() != n) {
		cout << "NIE";
		return 0;
	}
	cout << "TAK\n";
	for (int i : wynik) {
		cout << i << " ";
	}
	
	return 0;
}