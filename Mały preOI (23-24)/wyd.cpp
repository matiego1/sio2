#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 1000 * 1000;
vector<int> graf[MAX + 1];
vector<int> graf2[MAX + 1];

bool odwie[MAX + 1];
int order[MAX + 1];
int skladowa[MAX + 1];
int t = 1;
int waga[MAX + 1];
int poziom[MAX + 1];
vector<int> posortowane;
int dp[MAX + 1];

void dfs(int v) {
	odwie[v] = true;
	
	for (int u : graf[v]) {
		if (!odwie[u]) {
			dfs(u);
		}
	}
	
	order[t++] = v;
}

void sss(int v) {
	odwie[v] = true;
	skladowa[v] = t;
	
	for (int u : graf2[v]) {
		if (!odwie[u]) {
			sss(u);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b);
		graf2[b].push_back(a);
	}
	
	// Generowanie SSS
	for (int i = 1; i <= n; i++) {
		if (!odwie[i]) {
			dfs(i);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		odwie[i] = false;
	}
	
	t = 1;
	for (int i = n; i >= 1; i--) {
		if (!odwie[order[i]]) {
			sss(order[i]);
			t++;
		}
	}
	t--;

	for (int i = 1; i <= t; i++) {
		graf2[i].clear();
	}
	
	for (int i = 1; i <= n; i++) {
		for (int u : graf[i]) {
			if (skladowa[i] != skladowa[u]) {
				int pop = graf2[skladowa[i]].size();
				graf2[skladowa[i]].push_back(skladowa[u]);

				poziom[skladowa[u]]++;
			} else {
				waga[skladowa[i]]++;
			}
		}
	}
	
	// Sortowanie topologiczne
	
	queue<int> q;
	for (int i = 1; i <= t; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}
	
	while (!q.empty()) {
		int akt = q.front();
		q.pop();
		
		posortowane.push_back(akt);
		
		for (int u : graf2[akt]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
	}
	
	// Liczenie dynamika
	
	for (int i = posortowane.size() - 1; i >= 0; i--) {
		dp[posortowane[i]] = waga[posortowane[i]];
		
		int maks = -1;
		for (int u : graf2[posortowane[i]]) {
			maks = max(maks, dp[u]);
		}
		
		if (maks != -1) {
			dp[posortowane[i]] += maks + 1;
		}	
	}
	
	// Wypisanie wyniku
	
	for (int i = 1; i <= n; i++) {
		cout << dp[skladowa[i]] << "\n";
	}

	return 0;
}

