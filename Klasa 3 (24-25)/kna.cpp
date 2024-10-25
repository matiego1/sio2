#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

const int MAX_N = 5 * 1000;
const int MAX_W = 10 * 1000;

para wej[MAX_N + 1];
ll dp[MAX_W + 1];
ll pref[MAX_N + 1];
ll suff[MAX_N + 2];
priority_queue<int, vector<int>, greater<int>> q;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, w, k;
    cin >> n >> w >> k;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i].first >> wej[i].second;
    }

    sort(wej + 1, wej + 1 + n);

    for (int i = n; i >= 1; i--) {
        suff[i] = suff[i + 1];
        suff[i] += wej[i].second;
        q.push(wej[i].second);
        if (q.size() > k) {
            suff[i] -= q.top();
            q.pop();
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = w; j >= 0; j--) {
            if (j + wej[i].first <= w) {
                dp[j + wej[i].first] = max(dp[j + wej[i].first], dp[j] + wej[i].second);
            }
        }
        pref[i] = dp[w];
    }

    ll wynik = 0;
    for (int i = 0; i <= n; i++) {
        wynik = max(wynik, pref[i] + suff[i + 1]);
    }
    cout << wynik;

    return 0;
}
