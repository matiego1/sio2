#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
pair<int, int> order[MAX + 1];
int t = 0;

void dfs(int v) {
	order[v].first = (t++);
	for (int u : graf[v]) {
		dfs(u);
	}
	order[v].second = t - 1;
}

bool czy_poddrzewo(int a, int b) {
	return (order[a].first < order[b].first) && (order[b].first <= order[a].second);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 2; i <= n; i++) {
		int a;
		cin >> a;
		graf[a].push_back(i);
	}
	
	dfs(1);
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << (czy_poddrzewo(a, b) ? "TAK" : "NIE") << "\n";
	}

	return 0;
}

