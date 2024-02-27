#include <iostream>
using namespace std;

const int MAX = 100 * 1000;
int pyt1[MAX + 1];
int pyt2[MAX + 2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> pyt1[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> pyt2[i];
    }

    if (pyt1[1] != pyt2[1] && pyt1[3] == pyt2[3]) {
        cout << 1;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (pyt1[i] != pyt2[i]) {
            cout << i + 1;
            return 0;
        }
    }

    return 0;
}
