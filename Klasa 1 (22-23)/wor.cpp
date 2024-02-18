#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<long long, int> mapa;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    scanf("%d", &n);

    long long a;

    while(n--) {
        scanf("%lld", &a);
        mapa[a]++;
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%lld", &a);
        printf("%d\n", mapa[a]);
    }

    return 0;
}