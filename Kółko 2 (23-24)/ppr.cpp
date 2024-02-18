#include <iostream>
using namespace std;

const int R = (1 << 18);
int tree[2 * R];

void ustaw(int i, int x) {
	i += R;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

int maks(int a, int b) {
	a += R;
    b += R;
    int wynik = max(tree[a], tree[b]);
    while(a / 2 != b / 2) {
        if(a % 2 == 0) {
            wynik = max(wynik, tree[a + 1]);
        }
        if(b % 2 == 1) {
            wynik = max(wynik, tree[b - 1]);
        }
        a /= 2;
        b /= 2;
    }
    return wynik;
}

int main() {
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b, c;
		cin >> a >> b >> c;
		
		if (a == 0) {
			ustaw(b, c);
		} else {
			cout << maks(b, c) << "\n";
		}
	}

	return 0;
}

