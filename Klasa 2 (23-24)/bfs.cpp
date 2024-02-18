#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
int odleg[MAX + 1];
bool odwiedzone[MAX + 1];

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

    for (int i = 1; i <= n; i++) {
        odleg[i] = INF;
    }

    odleg[1] = 0;
    odwiedzone[1] = true;

    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : graf[v]) {
            if (!odwiedzone[u]) {
                odwiedzone[u] = true;
                odleg[u] = odleg[v] + 1;

                q.push(u);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (odleg[i] == INF ? -1 : odleg[i]) << "\n";
    }

    return 0;
}
