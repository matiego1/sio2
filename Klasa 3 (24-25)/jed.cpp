#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 300 * 1000;
int poz1[MAX + 1];
int poz2[MAX + 1];
int poz3[MAX + 1];
vector<pair<int, int>> wyst;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        poz1[a] = i;
    }
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        poz2[a] = i;
    }
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        poz3[a] = i;
    }

    for (int i = 1; i <= n; i++) {
        int a = (poz1[i] - poz2[i] + n) % n;
        int b = (poz1[i] - poz3[i] + n) % n;
        wyst.push_back({a, b});
    }

    sort(wyst.begin(), wyst.end());

    int wynik = 1, akt = 1;
    for (int i = 1; i < n; i++) {
        if (wyst[i - 1] != wyst[i]) {
            wynik = max(wynik, akt);
            akt = 0;
        }
        akt++;
    }
    cout << max(wynik, akt);

    return 0;
}
