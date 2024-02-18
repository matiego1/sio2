#include <iostream>
using namespace std;

const int R = 1 << 19;
long long tree[2 * R];

void sett(int i, int x) {
    i += R;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = tree[2 * i] ^ tree[2 * i + 1];
    }
}

long long gett(int a, int b) {
    a += R;
    b += R;
    long long wynik = tree[a];
    if (a != b) {
        wynik ^= tree[b];
    }
    while(a / 2 != b / 2) {
        if(a % 2 == 0) {
            wynik ^= tree[a + 1];
        }
        if(b % 2 == 1) {
            wynik ^= tree[b - 1];
        }
        a /= 2;
        b /= 2;
    }
    return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> tree[i + R];
    }
    for(int i = R - 1; i >= 1; i--) {
        tree[i] = tree[2 * i] ^ tree[2 * i + 1];
    }

    while (q--) {
        string typ;
        cin >> typ;
        int a, b;
        cin >> a >> b;
        if (typ == "zamien") {
            int pom = tree[a + R];
            sett(a, tree[b + R]);
            sett(b, pom);
        } else {
            cout << gett(a, b) << "\n";
        }
    }
    return 0;
}