#include <iostream>
using namespace std;

const int MAX = 10 * 1000 * 1000;
int sito[MAX + 1];

void wygeneruj_pierwsze() {
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

bool czy_pierwsze(int x) {
	if (x <= MAX) return sito[x];
	if (x % 2 == 0) return false;
	for (int i = 3; i * i <= x; i += 2) {
		if (x % i == 0) return false;
	}
	return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    wygeneruj_pierwsze();

    int n;
    cin >> n;

    while (n--) {
        int a;
        cin >> a;

        for (int i = a / 2; i >= 2; i--) {
            if (czy_pierwsze(i) && czy_pierwsze(a - i)) {
                if (i > a - i) {
                    cout << a - i << " " << i << "\n";
                } else {
                    cout << i << " " << a - i << "\n";
                }
                break;
            }
        }
    }

    return 0;
}
