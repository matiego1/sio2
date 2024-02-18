#include <iostream>
using namespace std;

const int R = (1 << 18);
long long tree[2 * R][6];

//void wypisz() {
//	cout << "---\n";
//	int potega = 1;
//	int pop = 0;
//	for (int i = 1; i < 2 * R; i++) {
//		cout << "[";
//		for (int j = 0; j < 6; j++) {
//			cout << tree[i][j];
//		}
//		cout << "] ";
//		if ((i - pop) == potega && i + 1 < 2 * R) {
//			potega *= 2;
//			pop = i;
//			cout << "| ";
//		}
//	}
//	cout << "\n---\n";
//}

void dodaj(int index, int wart) {
	index += R;
	tree[index][0] += wart;
	for (int i = 1; i < 6; i++) {
		tree[index][i] = (tree[index][0] % i == 0);
	}
	while (index > 1) {
		index /= 2;
		for (int i = 0; i < 6; i++) {
			tree[index][i] = tree[2 * index][i] + tree[2 * index + 1][i];
		}
	}
//	wypisz();
}

long long suma(int a, int b, int k) {
	a += R;
	b += R;
	long long wynik = tree[a][k];
	if (a != b) {
		wynik += tree[b][k];
	}
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			wynik += tree[a + 1][k];
		}
		if (b % 2 == 1) {
			wynik += tree[b - 1][k];
		}
		a /= 2;
		b /= 2;
	}
	return wynik;
}

int main() {
	int n, q;
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++) {
        tree[i + R][0] = 0;
		for (int j = 1; j < 6; j++) {
			tree[i + R][j] = 1;
		}
    }
    for(int i = R - 1; i >= 1; i--) {
		for (int j = 0; j < 6; j++) {
			tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
		}
    }
	
	while (q--) {
		string typ;
		cin >> typ;
		if (typ == "DODAJ") {
			int a, b;
			cin >> a >> b;
			dodaj(a, b);
		} else {
			int a, b, c;
			cin >> a >> b >> c;
			cout << suma(a, b, c) << "\n";
		}
	}
	
	return 0;
}
