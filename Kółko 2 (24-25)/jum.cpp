#include <iostream>
#include <vector>
using namespace std;

const int MAX = 500 * 1000;
vector<int> graf[MAX];
pair<int, int> order[MAX];
int pre = 0, post = 0;

void DFS(int v) {
	order[v] = make_pair(pre++, -1);
	for (int syn : graf[v]) {
		DFS(syn);
	}
	order[v].second = post++;
}

bool czy_przelozony(int a, int b) {
	return ((order[a].first < order[b].first) && (order[a].second > order[b].second));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a;
		cin >> a;
		graf[a].push_back(i);
	}
	
	DFS(0);
	
	int a, b;
	cin >> a;
	while (a != -1) {
		cin >> b;
		if (czy_przelozony(a, b)) {
			cout << "TAK\n";
		} else {
			cout << "NIE\n";
		}
		cin >> a;
	}
	
	return 0;
}