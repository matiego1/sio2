#include <set>
#include <iostream>
using namespace std;

const int MAX = 5 * 10000;
int wej[MAX];
set<int> wyst;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        wej[i] = wej[i - 1] + a;
        if (wej[i] == 0) {
            cout << "TAK";
            return 0;
        }
        if (wyst.find(wej[i]) != wyst.end()) {
            cout << "TAK";
            return 0;
        }
        wyst.insert(wej[i]);
    }

    cout << "NIE";

    return 0;
}
