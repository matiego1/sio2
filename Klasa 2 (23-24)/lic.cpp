#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
const int R = (1 << 19);

para wej_sort[MAX + 1];
int wej[MAX + 1];
para dp[MAX + 1];
para tree[2 * R];
int MOD;

para maks_par(para a, para b) {
	if (a.first > b.first) return a;
	if (b.first > a.first) return b;
	a.second = (a.second + b.second) % MOD;
	return a;
}

void ustaw(int indeks, para wart) {
	indeks += R;
	tree[indeks] = maks_par(tree[indeks], wart);
	while (indeks > 1) {
		indeks /= 2;
		tree[indeks] = maks_par(tree[2 * indeks], tree[2 * indeks + 1]);
	}
}

para maksimum(int b) {
	int a = R;
	b += R;
	para wynik = maks_par(tree[a], tree[b]);
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			wynik = maks_par(wynik, tree[a + 1]);
		}
		if (b % 2 == 1) {
			wynik = maks_par(wynik, tree[b - 1]);
		}
		a /= 2;
		b /= 2;
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n >> MOD;
	
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		wej_sort[i] = {a, i};
	}
	
	sort(wej_sort + 1, wej_sort + 1 + n);
	
	wej[wej_sort[1].second] = 1;
	int indeks = 1;
	for (int i = 2; i <= n; i++) {
		if (wej_sort[i].first != wej_sort[i - 1].first) {
			indeks++;
		}
		wej[wej_sort[i].second] = indeks;
	}
	
	int dlugosc = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = maksimum(wej[i] - 1);
		dp[i].first++;
		if (dp[i].second == 0) {
			dp[i].second = 1;
		}
		dlugosc = max(dlugosc, dp[i].first);
		ustaw(wej[i], dp[i]);
	}
	
	
	int wynik = 0;
	for (int i = 1; i <= n; i++) {
		if (dp[i].first == dlugosc) {
			wynik = (wynik + dp[i].second) % MOD;
		}
	}
	cout << wynik;

	return 0;
}

