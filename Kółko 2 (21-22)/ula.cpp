#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
vector<int> graf_odw[MAX + 1];
set<int> graf_skl[MAX + 1];
int wej[MAX + 1];
bool odwie[MAX + 1];
int order[MAX + 1];
int sklad[MAX + 1];
int dp[MAX + 1];
int poziom[MAX + 1];
int t = 0;

void dfs(int v) {
	odwie[v] = true;
	for (int u : graf[v]) {
		if (!odwie[u]) {
			dfs(u);
		}
	}
	order[++t] = v;
}

void sss(int v) {
	odwie[v] = true;
	sklad[v] = t;
	dp[t] += wej[v];
	for (int u : graf_odw[v]) {
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

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
    }

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graf[a].push_back(b);
        graf_odw[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
		if (!odwie[i]) {
			dfs(i);
		}
	}

	t = 0;
	for (int i = 1; i <= n; i++) {
		odwie[i] = false;
	}

	for (int i = n; i >= 1; i--) {
		if (!odwie[order[i]]) {
			t++;
			sss(order[i]);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int u : graf[i]) {
			if (sklad[i] != sklad[u]) {
				graf_skl[sklad[i]].insert(sklad[u]);
			}
		}
	}
	for (int i = 1; i <= t; i++) {
		for (int u : graf_skl[i]) {
			poziom[u]++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= t; i++) {
		if (poziom[i] == 0) {
			q.push(i);
		}
	}

	vector<int> topo;
	while (!q.empty()) {
		int akt = q.front();
		q.pop();
		topo.push_back(akt);
		for (int u : graf_skl[akt]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
	}

	int wynik = 0;
	for (int i = topo.size() - 1; i >= 0; i--) {
        int maks = 0;
        for (int u : graf_skl[topo[i]]) {
            maks = max(maks, dp[u]);
        }
        dp[topo[i]] += maks;

        wynik = max(wynik, dp[topo[i]]);
	}

	cout << wynik;

    return 0;
}
