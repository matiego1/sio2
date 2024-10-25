#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

const int MAX = 200 * 1000;

vector<int> graf[MAX + 1];
int wej[MAX + 1];
int dp[MAX + 1];
int wynik[MAX + 1];

void dfs1(int v, int p) {
    dp[v] = wej[v];
    for (int u : graf[v]) {
        if (u == p) continue;
        dfs1(u, v);
        dp[v] += max(0, dp[u]);
    }
}

void dfs2(int v, int p) {
    for (int u : graf[v]) {
        if (u == p) continue;

        dp[v] -= max(0, dp[u]);
        dp[u] += max(0, dp[v]);

        wynik[u] = dp[u];

        dfs2(u, v);

        dp[u] -= max(0, dp[v]);
        dp[v] += max(0, dp[u]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        wej[i] = (a == 1 ? 1 : -1);
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;

        graf[a].push_back(b);
        graf[b].push_back(a);
    }

    dfs1(1, 1);
    wynik[1] = dp[1];
    dfs2(1, 1);

    for (int i = 1; i <= n; i++) {
        cout << wynik[i] << " ";
    }

    return 0;
}
