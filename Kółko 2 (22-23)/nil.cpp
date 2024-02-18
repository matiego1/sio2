#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
int waga[MAX + 1];

long long DP[MAX + 1];

void DFS(int v, int o) {
	long long maks = 0;
	for (int syn : graf[v]) {
		if (syn != o) {
			DFS(syn, v);
			maks = max(maks, DP[syn]);
		}
	}
	DP[v] = maks + waga[v];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> waga[i];
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	DFS(1, 0);
	
	cout << DP[1];
	
	return 0;	
}
