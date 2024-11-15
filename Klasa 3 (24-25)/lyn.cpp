#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int INF = (1 << 30);
const int MAX = 200 * 1000;
int przed[MAX + 1];
int wyst[MAX + 1];
int graf[MAX + 1];
int graf_pom[MAX + 1];
int pom[MAX + 1];
int koniec[MAX + 1];

void zloz(int m, int (&f)[MAX + 1], int (&g)[MAX + 1]) {
    for (int i = 1; i <= m; i++) {
        pom[i] = f[g[i]];
    }
    for (int i = 1; i <= m; i++) {
    	f[i] = pom[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q;
	
	int pop = -1, pierwsze = -1;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		if (pierwsze == -1) pierwsze = a;
		przed[a] = pop;
		pop = a;
	}
	przed[pierwsze] = pop;
	
	for (int i = 1; i <= m; i++) {
		int a;
		cin >> a;
		graf[i] = i;
		graf_pom[i] = wyst[przed[a]];
		wyst[a] = i;
	}
	
	n -= 1;
	while (n) {
		if (n & 1) {
			zloz(m, graf, graf_pom);
		}
		zloz(m, graf_pom, graf_pom);
		n /= 2;
	}
	
	for (int i = 1; i <= m; i++) {
		koniec[i] = INF;
	}
	for (int i = 1; i <= m; i++) {
		koniec[graf[i]] = min(koniec[graf[i]], i);
	}
	for (int i = m - 1; i >= 1; i--) {
		koniec[i] = min(koniec[i], koniec[i + 1]);
	}
	
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << (koniec[a] <= b ? 1 : 0);
	}
	
	return 0;
}


