#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int kra[MAX + 1];
pair<int, int> minMax[MAX + 1];
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

    masa[b] += masa[a];
    minMax[b].first = min(minMax[b].first, minMax[a].first);
    minMax[b].second = max(minMax[b].second, minMax[a].second);
    kra[a] = b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        kra[i] = i;
        int a, b;
        cin >> a >> b;
        minMax[i] = make_pair(b, b);
        masa[i] = a;
    }

    string typ;
    while (cin >> typ) {
        if (typ == "JOIN") {
            int a, b;
            cin >> a >> b;
            unionn(a, b);
        } else if (typ == "IQ_MIN") {
            int a;
            cin >> a;
            cout << minMax[findd(a)].first << "\n";
        } else if (typ == "IQ_MAX") {
            int a;
            cin >> a;
            cout << minMax[findd(a)].second << "\n";
        } else if (typ == "MASA") {
            int a;
            cin >> a;
            cout << masa[findd(a)] << "\n";
        }
    }

    return 0;
}