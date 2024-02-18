#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, a, b;
    cin >> n >> a >> b;

    int tab[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> tab[i];
    }

    sort(tab + a, tab + b + 1);

    for (int i = 1; i <= n; i++) {
        cout << tab[i] << " ";
    }

    return 0;
}
