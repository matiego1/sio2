#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 1000 * 1000;
ll pref[MAX + 1];
unordered_map<ll, int> wyst;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        pref[i] = pref[i - 1] + (c == 'O' ? -1 : k);

        if (wyst[pref[i]] == 0) {
            wyst[pref[i]] = i;
        }
    }

    int wynik = 0;
    for (int i = n; i >= 1; i--) {
        if (pref[i] == 0) {
            wynik = max(wynik, i);
            continue;
        }
        int pop = wyst[pref[i]];
        if (pop == 0) continue;
        wynik = max(wynik, i - pop);
    }
    cout << wynik;

    return 0;
}
