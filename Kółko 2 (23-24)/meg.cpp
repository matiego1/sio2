#include <iostream>
#include <vector>
using namespace std;

const int MAX = 250 * 1000;
const int R = (1 << 18);
vector<int> graf[MAX + 1];
pair<int, int> order[MAX + 1];
int h[MAX + 1];
int t = 0;
int tree[2 * R];

void dfs(int v, int p) {
	order[v].first = ++t;
	
	for(int u : graf[v]) {
		if (u != p) {
			h[u] = h[v] + 1;
			dfs(u, v);
		}
	}
	
	order[v].second = t;
}

void zmien(int a, int b) {
	a += R;
	b += R;
	tree[a]++;
	if (a != b) {
		tree[b]++;
	}
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			tree[a + 1]++;
		}
		if (b % 2 == 1) {
			tree[b - 1]++;
		}
		a /= 2;
		b /= 2;
	}
}

int pytanie(int a) {
	a += R;
	int wynik = 0;
	while (a > 0) {
		wynik += tree[a];
		a /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	dfs(1, 1);
	
	int m;
	cin >> m;
	
	for (int i = 0; i < n + m - 1; i++) {
		string typ;
		cin >> typ;
		if (typ == "A") {
			int a, b;
			cin >> a >> b;
			if (h[b] > h[a]) swap(a, b);
			zmien(order[a].first, order[a].second);
		} else {
			int a;
			cin >> a;
			cout << h[a] - pytanie(order[a].first) << "\n";
		}
	}
	
	return 0;
}