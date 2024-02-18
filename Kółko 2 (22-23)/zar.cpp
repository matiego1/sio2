#include <iostream>
using namespace std;

const int R = (1 << 20);
int tree[2 * R];

void zmien(int a, int b) {
	a += R;
	b += R;
	tree[a]++;
	if (a != b) {
		tree[b]++;
	}
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			tree[a + 1]++;
		}
		if (b % 2 == 1) {
			tree[b - 1]++;
		}
		a /= 2;
		b /= 2;
	}
}

int pytanie(int index) {
	index += R;
	int wynik = 0;
	while (index >= 1) {
		wynik += tree[index];
		index /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	string wej;
	cin >> wej;
	
	for (int i = 0; i < wej.length(); i++) {
		if (wej[i] == 'o') {
			zmien(i + 1, i + 1);
		}
	}
	
	while(q--) {
        string typ;
        cin >> typ;
        if (typ == "Q") {
			int a;
			cin >> a;
			if (pytanie(a) % 2 == 0) {
				cout << "OFF\n";
			} else {
				cout << "ON\n";
			}
		} else {
			int a, b;
			cin >> a >> b;
			zmien(a, b);
		}
    }
	return 0;
}
