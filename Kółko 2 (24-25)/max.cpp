#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int R = (1 << 18);
int tree[2 * R];
void ustaw(int indeks, int wart) {
	indeks += R;
	tree[indeks] = wart;
	while (indeks > 1) {
		indeks /= 2;
		tree[indeks] = max(tree[2 * indeks], tree[2 * indeks + 1]);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		ustaw(i, x);
	}
	
	cout << tree[1] << "\n";
	
	while (m--) {
		int i, x;
		cin >> i >> x;
		ustaw(i, x);
		cout << tree[1] << "\n";
	}

	return 0;
}

