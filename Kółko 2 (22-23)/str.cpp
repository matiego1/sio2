#include <iostream>
#include <vector>
using namespace std;

const int MAX = 500 * 1000;
vector<int> graf[MAX + 1];
bool strajki[MAX + 1];
int ojcowie[MAX + 1];
int dzieci[MAX + 1];
int zle_dzieci[MAX + 1];

int dobre_dzieci(int v) {
	return dzieci[v] - zle_dzieci[v] + (strajki[ojcowie[v]] ? 0 : 1);
}

void dfs(int v, int ojciec) {
	ojcowie[v] = ojciec;
	dzieci[ojciec]++;
	for (int u : graf[v]) {
		if (u != ojciec) {
			dfs(u, v);
		}
	}
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
	
	strajki[0] = true;
	dfs(1, 0);
	
	int czesci = 1;
	
	int m;
	cin >> m;
	
	while (m--) {
		int a;
		cin >> a;
		
		if (a > 0) {
			strajki[a] = true;
			zle_dzieci[ojcowie[a]]++;
			
			czesci += dobre_dzieci(a) - 1;
		} else {
			strajki[-a] = false;
			zle_dzieci[ojcowie[-a]]--;
			
			czesci -= dobre_dzieci(-a) - 1;
		}
		
		cout << czesci << "\n";
	}
	
	return 0;
}

