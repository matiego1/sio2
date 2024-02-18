#include <iostream>
using namespace std;
typedef long long ll;

const int MAX = 1000;
pair<ll, ll> punkty[MAX + 1];
bool odwie[MAX + 1];

ll odleg(int a, int b) {
    return ((punkty[a].first - punkty[b].first) * (punkty[a].first - punkty[b].first)) + ((punkty[a].second - punkty[b].second) * (punkty[a].second - punkty[b].second));
}

void dfs(int v, int n, ll s) {
    odwie[v] = true;
    for (int i = 1; i <= n; i++) {
        if (!odwie[i] && odleg(v, i) <= s * s) dfs(i, n, s);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    ll s;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        punkty[i] = make_pair(a, b);
    }

    dfs(1, n, s);

    int wynik = 0;
    for (int i = 1; i <= n; i++) {
        wynik += odwie[i];
    }
    cout << wynik;

    return 0;
}
