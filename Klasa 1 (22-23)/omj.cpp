#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int tab[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        tab[i] = tab[i - 1] + a;
    }

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", (tab[b] - tab[a - 1]));
    }

    return 0;
}
