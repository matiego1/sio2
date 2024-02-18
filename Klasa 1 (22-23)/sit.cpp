#include <iostream>
using namespace std;

const int MAX = 2 * 1000 * 1000;
bool sito[MAX + 1];

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

    int n;
    cin >> n;
    int ile = 0;
    for (int i = 2; i <= MAX; i++) {
        if (sito[i]) {
            cout << i << " ";
            ile++;
            if (ile == n) return 0;
        }
    }

    return 0;
}
