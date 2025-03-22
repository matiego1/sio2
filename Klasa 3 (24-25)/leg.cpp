#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int R = (1 << 17);
const int GORA = R;
const int DOL = 3 * R;
const int MAX = DOL + 2 * R;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
vector<para> graf[MAX];
ll odleg[MAX];

void stworz_gora(int pocz, int kon, int v, int w) {
    pocz += R - 1;
    kon += R + 1;
    while (pocz / 2 != kon / 2) {
        if (pocz % 2 == 0) {
            graf[v].push_back({pocz + 1 + GORA, w});
        }
        if (kon % 2 == 1) {
            graf[v].push_back({kon - 1 + GORA, w});
        }
        pocz /= 2;
        kon /= 2;
    }
}

void stworz_dol(int pocz, int kon, int v, int w) {
    pocz += R - 1;
    kon += R + 1;
    while (pocz / 2 != kon / 2) {
        if (pocz % 2 == 0) {
            graf[pocz + 1 + DOL].push_back({v, w});
        }
        if (kon % 2 == 1) {
            graf[kon - 1 + DOL].push_back({v, w});
        }
        pocz /= 2;
        kon /= 2;
    }
}

void dijkstra(int start) {
    for (int i = 1; i < MAX; i++) {
        odleg[i] = INF;
    }

    priority_queue<para, vector<para>, greater<para>> q;

    odleg[start] = 0;
    q.push({0, start});

    while (!q.empty()) {
        int v = (int) q.top().second;
        q.pop();
        
        for (para p : graf[v]) {
            int u = (int) p.first;
            ll w = p.second;
            
            if (odleg[u] > odleg[v] + w) {
                odleg[u] = odleg[v] + w;
                q.push({odleg[u], u});
			}
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q, s;
    cin >> n >> q >> s;

    for (int i = R - 1; i >= 1; i--) {
        graf[i + GORA].push_back({2 * i + GORA, 0});
        graf[i + GORA].push_back({2 * i + 1 + GORA, 0});

        graf[2 * i + DOL].push_back({i + DOL, 0});
        graf[2 * i + 1 + DOL].push_back({i + DOL, 0});
    }
    for (int i = R; i < 2 * R; i++) {
        graf[i + GORA].push_back({i - R + 1, 0});
        graf[i - R + 1].push_back({i + DOL, 0});
    }


    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, u, w;
            cin >> v >> u >> w;
            graf[v].push_back({u, w});
        } else {
            int v, l, r, w;
            cin >> v >> l >> r >> w;
			l--;
			r--;

            if (t == 2) {
                stworz_gora(l, r, v, w);
            } else {
                stworz_dol(l, r, v, w);
            }
        }
    }

    dijkstra(s);

    for (int i = 1; i <= n; i++) {
        if (odleg[i] == INF) {
            cout << "-1 ";
        } else {
            cout << odleg[i] << " ";
        }
    }

    return 0;
}
