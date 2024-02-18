#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int MAX = 500 * 1000;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
vector<para> graf[MAX + 1];
ll odleg[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        graf[a].push_back(make_pair(b, c));
        graf[b].push_back(make_pair(a, c));
    }

    for (int i = 1; i <= n; i++) {
        odleg[i] = INF;
    }

    priority_queue<para, vector<para>, greater<para>> q;

    odleg[1] = 0;
    q.push(make_pair(0, 1));

    while (!q.empty()) {
        int v = q.top().second;
        q.pop();

        for (para p : graf[v]) {
            int u = p.first;
            int w = p.second;

            if (odleg[u] > odleg[v] + w) {
                odleg[u] = odleg[v] + w;
                q.push(make_pair(odleg[u], u));
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (odleg[i] == INF ? -1 : odleg[i]) << "\n";
    }

    return 0;
}