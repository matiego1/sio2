#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
int wej[MAX + 1];
priority_queue<para, vector<para>, greater<para>> q;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
    }

    sort(wej + 1, wej + 1 + n);

    para akt = {wej[1], 1};
    q.push({wej[1], 1});

    for (int i = 1; i <= k; i++) {
        akt = q.top();
        q.pop();

        if (akt.second + 1 > n) continue;

        q.push({akt.first + wej[akt.second + 1], akt.second + 1});
        q.push({akt.first - wej[akt.second] + wej[akt.second + 1], akt.second + 1});
    }

    cout << akt.first;

    return 0;
}
