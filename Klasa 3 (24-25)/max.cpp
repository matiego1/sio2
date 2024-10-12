#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> para;
 
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX = 200 * 1000;
ll wej[MAX + 1];
ll pref[MAX + 1];
 
priority_queue<para, vector<para>, greater<para>> q;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int n, a, b;
    cin >> n >> a >> b;
 
    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
        pref[i] = pref[i - 1] + wej[i];
    }
 
    ll wynik = -INF;
    for (int i = a; i <= n; i++) {
        q.push({pref[i - a], i - a});
 
        para p;
        while ((p = q.top()).second < i - b) q.pop();
 
        wynik = max(wynik, pref[i] - p.first);
    }
 
    cout << wynik;
 
    return 0;
}
