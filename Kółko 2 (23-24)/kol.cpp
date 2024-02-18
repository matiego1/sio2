#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int kra[MAX + 1];

int mini[MAX + 1];
int maks[MAX + 1];
int masa[MAX + 1];

int findd(int x) {
    if (kra[x] == x) return x;
    kra[x] = findd(kra[x]);
    return kra[x];
}

void unionn(int a, int b) {
    a = findd(a);
    b = findd(b);
    if (a == b) return;
    
    kra[a] = b;
    
    masa[b] += masa[a];
    mini[b] = min(mini[b], mini[a]);
    maks[b] = max(maks[b], maks[a]);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        kra[i] = i;
        
        int a, b;
        scanf("%d %d", &a, &b);

        mini[i] = b;
        maks[i] = b;
        masa[i] = a;
    }

    char typ[10];
    while (scanf("%s", &typ) != EOF) {
        if (typ[0] == 'J') {
            int a, b;
            scanf("%d %d", &a, &b);
            unionn(a, b);
        } else if (typ[0] == 'I' && typ[4] == 'I') {
            int a;
            scanf("%d", &a);
            printf("%d\n", mini[findd(a)]);
        } else if (typ[0] == 'I' && typ[4] == 'A') {
            int a;
            scanf("%d", &a);
            printf("%d\n", maks[findd(a)]);
        } else if (typ[0] == 'M') {
            int a;
            scanf("%d", &a);
            printf("%d\n", masa[findd(a)]);
        }
    }

    return 0;
}
