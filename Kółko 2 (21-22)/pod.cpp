#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef pair<ll, ll> para;

struct Sciezka {
    ll cel, koszt, pierwszy_kurs, co_ile;
};

const ll INF = 18ull * 1000 * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX = 300 * 1000;
vector<Sciezka> graf[MAX + 1];
priority_queue<para, vector<para>, greater<para>> q;
ll odleg[MAX + 1];

void dijkstra(int n) {
    odleg[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        int v = q.top().second;
        q.pop();

        for (Sciezka s : graf[v]) {
            ll koszt_czekania = 0;
            if (odleg[v] <= s.pierwszy_kurs) {
                koszt_czekania = s.pierwszy_kurs - odleg[v];
            } else {
                ll akt = odleg[v] - s.pierwszy_kurs;
                if (akt % s.co_ile == 0) {
                    koszt_czekania = 0;
                } else {
                    koszt_czekania = ((akt / s.co_ile) + 1) * s.co_ile - akt;
                }
            }
            if (odleg[s.cel] > odleg[v] + s.koszt + koszt_czekania) {
                odleg[s.cel] = odleg[v] + s.koszt + koszt_czekania;
                q.push({odleg[s.cel], s.cel});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;

        for (int j = 1; j <= m; j++) {
            ll a, b, c, d;
            cin >> a >> b >> c >> d;
            graf[i].push_back({a, b, c, d});
        }
    }

    for (int i = 1; i <= n; i++) {
        odleg[i] = INF;
    }

    dijkstra(n);

    if (odleg[n] == INF) {
        cout << "ARESZT";
    } else {
        cout << odleg[n];
    }

    return 0;
}
