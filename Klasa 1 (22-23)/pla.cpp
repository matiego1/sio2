#include <iostream>
#include <algorithm>
using namespace std;

bool rozwiaz() {
    int n;
    cin >> n;
    pair<int, int> czasy[n];
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        czasy[i] = make_pair(a, b);
    }
    sort(czasy, czasy + n);
    for (int i = 1; i < n; i++) {
        if (czasy[i].first < czasy[i - 1].second) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        cout << (rozwiaz() ? "TAK\n" : "NIE\n");
    }

    return 0;
}
