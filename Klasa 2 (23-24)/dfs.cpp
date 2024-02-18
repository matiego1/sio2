#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
bool odwie[MAX + 1];

void dfs(int v) {
    odwie[v] = true;
    for (int u : graf[v]) {
        if (!odwie[u]) dfs(u);
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
        graf[b].push_back(a);
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        cout << (odwie[i] ? "TAK" : "NIE") << "\n";
    }

    return 0;
}
