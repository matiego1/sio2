#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
int wej[MAX + 1];
int pref[MAX + 1];
int frag[MAX + 1];

priority_queue<para, vector<para>, greater<para>> q;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    const int sufit = (n + 1) / 2;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
        pref[i] = pref[i - 1] + wej[i];
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        wej[i] = wej[i - n];
        pref[i] = pref[i - 1] + wej[i];
    }

    for (int i = 1; i <= 2 * n; i++) {
        frag[i] = pref[i + sufit - 1] - pref[i - 1];
    }

    for (int i = 1; i < sufit; i++) {
        q.push({frag[i], i});
    }

    int wynik = 0;

    for (int pocz = 1; pocz <= n; pocz++) {
        int kon = pocz + sufit - 1;
        q.push({frag[kon], kon});

        while (q.top().second < pocz) q.pop();

        wynik = max(wynik, q.top().first);
    }

    cout << wynik;

    return 0;
}
