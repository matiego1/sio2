#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
bool sito[MAX + 1];
int pref[MAX + 1];

void pierwsze() {
    for (int i = 2; i <= MAX; i++) {
        sito[i] = true;
    }

    for (int i = 2; i * i <= MAX; i++) {
        if (sito[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                sito[j] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    pierwsze();

    for (int i = 2; i <= MAX; i++) {
        pref[i] = pref[i - 1] + sito[i];
    }

    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        cout << pref[b] - pref[a - 1] << "\n";
    }

    return 0;
}
