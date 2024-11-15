#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const int LOG = 30;
vector<int> graf[MAX + 1];
int prz[MAX + 1][LOG + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        prz[i][0] = a;
	}

	for (int i = 1; i <= LOG; i++) {
        for (int v = 1; v <= n; v++) {
            prz[v][i] = prz[prz[v][i - 1]][i - 1];
        }
	}

    for (int i = 1; i <= q; i++) {
        int x, k;
        cin >> x >> k;

        int wynik = x;
        for (int i = LOG; i >= 0; i--) {
            if ((1 << i) > k) continue;
            k -= (1 << i);
            wynik = prz[wynik][i];
        }
        cout << wynik << "\n";
    }

	return 0;
}
