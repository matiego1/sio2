#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
const int R = (1 << 20);
int wej[MAX + 1];
para tab[MAX + 1];
int tree[2 * R];

void ustaw(int indeks, int x) {
    indeks += R;
    tree[indeks] = max(tree[indeks], x);

    while (indeks > 1) {
        indeks /= 2;
        tree[indeks] = max(tree[2 * indeks], tree[2 * indeks + 1]);
    }
}

int query(int pocz, int kon) {
    pocz += R;
    kon += R;
    int wynik = max(tree[pocz], tree[kon]);
    while (pocz / 2 != kon / 2) {
        if (pocz % 2 == 0) {
            wynik = max(wynik, tree[pocz + 1]);
        }
        if (kon % 2 == 1) {
            wynik = max(wynik, tree[kon - 1]);
        }
        pocz /= 2;
        kon /= 2;
    }
    return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
        tab[i] = {wej[i], i};
    }

    sort(tab + 1, tab + 1 + n);
    int indeks = 1;
    for (int i = 1; i <= n; i++) {
    	wej[tab[i].second] = indeks;
    	if (i < n && tab[i].first != tab[i + 1].first) indeks++;
    }

    int wynik = 1;
    for (int i = 1; i <= n; i++) {
        int wart = query(0, wej[i] - 1) + 1;
        ustaw(wej[i], wart);
        wynik = max(wynik, wart);
    }

    cout << wynik;

	return 0;
}
