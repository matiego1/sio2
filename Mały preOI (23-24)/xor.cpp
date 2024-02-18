#include <iostream>
using namespace std;

typedef unsigned long long ull;

const int MAX = 20;
ull wej[MAX + 1][MAX + 1];
int n, m;
ull k;

ull wynik = 0;
int dol[MAX];

ull policz() {
	ull wynik = wej[1][1];
	
	int x = 1, y = 1;
	
	for (int i = 0; i <= m; i++) {
		// w dol
		for (int j = 0; j < dol[i]; j++) {
			y++;
			wynik ^= wej[y][x];
		}
		// w prawo
		x++;
		wynik ^= wej[y][x];
	}
	
	return wynik;
}

void rekur(int indeks, int ruchy) {
	if (indeks + 1 == m) {
		dol[indeks] = ruchy;
		if (policz() == k) {
			wynik++;
		}
		return;
	}
	
	for (int i = 0; i <= ruchy; i++) {
		dol[indeks] = i;
		rekur(indeks + 1, ruchy - i);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> wej[i][j];
		}
	}
	
	rekur(0, n - 1);
	
	cout << wynik;

	return 0;
}

