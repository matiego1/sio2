#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 10 * 1000;
vector<int> graf[MAX + 1];
vector<int> graf2[MAX + 1];
int poziom[MAX + 1];
bitset<MAX + 1> odwie[MAX + 1];
queue<int> q;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf2[b].push_back(a);
		poziom[a]++;
	}
	
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		odwie[v].set(v);
		for (int u : graf[v]) {
			odwie[v] |= odwie[u];
		}
		
		for (int p : graf2[v]) {
			poziom[p]--;
			if (poziom[p] == 0) {
				q.push(p);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << odwie[i].count() << " ";
	}

	return 0;
}