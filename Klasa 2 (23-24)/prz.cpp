#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 200 * 1000;
pair<int, int> wej[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        wej[i] = make_pair(b, a);
    }

    sort(wej, wej + n);

    int koniec = 0;
    int wynik = 0;

    for (int i = 0; i < n; i++) {
        int a = wej[i].second, b = wej[i].first;
        if (a < koniec) continue;
        wynik++;
        koniec = b;
    }

    cout << wynik;

    return 0;
}
