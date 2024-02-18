#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1000 * 1000;
pair<int, int> tab[MAX];

int policz(int s) {
    int d = s % 10;
    s /= 10;
    int c = s % 10;
    s /= 10;
    int b = s % 10;
    s /= 10;
    int a = s;

    d += 10 * a;
    c += 10 * d;
    b += 10 * c;

    return b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        tab[i] = make_pair(policz(a), a);
    }

    sort(tab, tab + n);

    for (int i = 0; i < n; i++) {
        cout << tab[i].second << " ";
    }

    return 0;
}

