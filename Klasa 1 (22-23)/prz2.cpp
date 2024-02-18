#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
long long tyg[MAX + 1];
long long smo[MAX + 1];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    scanf("%d %d", &n, &q);
    //cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        //cin >> a;
        tyg[i] = tyg[i - 1];
        smo[i] = smo[i - 1];
        if (a == 3) {
            tyg[i]++;
        } else if (a == 4) {
            smo[i]++;
        }
    }

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        //cin >> a >> b;

        printf("%d %d\n", (tyg[b] - tyg[a - 1]), (smo[b] - smo[a - 1]));
        //cout << (tyg[b] - tyg[a - 1]) << " " << (smo[b] - smo[a - 1]) << "\n";
    }

    return 0;
}
