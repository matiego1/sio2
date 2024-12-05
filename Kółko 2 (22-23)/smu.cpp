#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int K = 2;
struct Node {
	bool ustawione = false;
	ll wart[K][K];
};
const Node PUSTE = {false, {{0, 0}, {0, 0}}};

const int MOD = 1000 * 1000 * 1000 + 7;
const int R = (1 << 18);
Node tree[2 * R];

Node generuj(char c) {
	if (c == 'S' || c == 'D') {
		return {true, {{0, 0}, {1, 1}}};
	}
	if (c == 'H') {
		return {true, {{1, 1}, {0, 0}}};
	}
	if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
		return {true, {{0, 1}, {1, 0}}};
	}
	if (c == '?') {
		return {true, {{19, 6}, {7, 20}}};
	}
	return {true, {{1, 0}, {0, 1}}};
}

Node polacz(Node lewy, Node prawy) {
	if (!lewy.ustawione && !prawy.ustawione) return PUSTE;
	if (!lewy.ustawione) return prawy;	
	if (!prawy.ustawione) return lewy;
	
	Node wynik = {true, {{0, 0}, {0, 0}}};
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			ll akt = 0;
			for (int k = 0; k < K; k++) {
				akt += prawy.wart[i][k] * lewy.wart[k][j];
				if (akt >= MOD) akt %= MOD;
			}
			wynik.wart[i][j] = akt;
		}
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		tree[R + i] = generuj(c);
	}
	
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = polacz(tree[2 * i], tree[2 * i + 1]);
	}
	
	cout << tree[1].wart[0][0] << "\n";
	
	while (q--) {
		int indeks;
		cin >> indeks;
		char c;
		cin >> c;
		
		indeks += R;
		tree[indeks] = generuj(c);
		while (indeks > 1) {
			indeks /= 2;
			tree[indeks] = polacz(tree[2 * indeks], tree[2 * indeks + 1]);
		}
		
		cout << tree[1].wart[0][0] << "\n";
	}

	return 0;
}

