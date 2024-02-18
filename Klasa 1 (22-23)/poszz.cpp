#include <iostream>
#include <map>
using namespace std;

map<int, int> wej;

int znajdz(int wart) {
    auto x = wej.lower_bound(wart);
    if (x == wej.end()) {
        return -1;
    }
    return (*x).second;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        if (wej[a] == 0) {
        	wej[a] = i;
		} else {
        	wej[a] = min(wej[a], i);
		}
    }

    while (q--) {
        int a;
        scanf("%d", &a);
        int w = znajdz(a);
        if (w == -1) {
            printf("AAAAAAAAAAAAAAAAAA!11!!1!!\n");
        } else {
            printf("%d\n", w);
        }
    }

    return 0;
}
