#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> para;

const int MAX = 100 * 1000;

vector<para> graf[MAX + 1]; //A = 1; B = -1
bool odwie[MAX + 1];
int ksztalt[MAX + 1]; //1 lub -1

void dfs(int v, int k) {
	if (odwie[v]) return;
	odwie[v] = true;
	ksztalt[v] = k;
	
	for (para p : graf[v]) {
		dfs(p.first, k * p.second);
	}
}

bool rozwiaz() {
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i <= MAX; i++) {
		graf[i].clear();
		odwie[i] = false;
		ksztalt[i] = 0;
	}
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		char c;
		cin >> c;
		
		int k = (c == 'A' ? 1 : -1);
		
		graf[a].push_back(make_pair(b, k));
		graf[b].push_back(make_pair(a, k));
	}
	
	for (int i = 1; i <= n; i++) {
		if (!odwie[i]) {
			dfs(i, true);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (para p : graf[i]) {
			if (ksztalt[i] != ksztalt[p.first] * p.second) {
				return false;
			}
		}
	}
	
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		cout << (rozwiaz() ? "TAK" : "NIE") << "\n";
	}

	return 0;
}

