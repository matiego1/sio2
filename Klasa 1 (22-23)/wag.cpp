#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 20 * 1000;
pair<int, int> tab[MAX];

//x << y = x * (2 ** y)
bool f(pair<int, int>& a, pair<int, int>& b) {
    int x1 = (a.first << b.second);
    int x2 = (b.first << a.second);
    if (x1 == x2) {
        return a.first < b.first;
    }
    return x1 < x2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tab[i] = make_pair(a, b);
    }

    sort(tab, tab + n, f);

    for (int i = 0; i < n; i++) {
        cout << tab[i].first << " " << tab[i].second << "\n";
    }

    return 0;
}

