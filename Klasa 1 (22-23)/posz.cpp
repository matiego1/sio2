#include <iostream>
#include <set>
using namespace std;

const int MAX = 1000 * 1000;
set<int> wej;

int znajdz(int wart) {
    auto x = wej.lower_bound(wart);
    if (x == wej.end()) {
        return -1;
    }
    return (*x);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    scanf("%d %d", &n, &q);
    //cin >> n >> q;

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        //cin >> a;
        wej.insert(a);
    }

    while (q--) {
        int a;
        scanf("%d", &a);
        //cin >> a;
        int w = znajdz(a);
        if (w == -1) {
            printf("AAAAAAAAAAAAAAAAAA!11!!1!!\n");
            //cout << "AAAAAAAAAAAAAAAAAA!11!!1!!\n";
        } else {
            printf("%d\n", w);
            //cout << w << "\n";
        }
    }

    return 0;
}
