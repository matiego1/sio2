#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000 * 1000;
int wej[MAX];
int tab[MAX];
int ps[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
        cin >> wej[i];
	}

	tab[0] = INT_MIN;

	int pop;
	cin >> pop;
	for (int i = 1; i < m; i++) {
        int a;
        cin >> a;
        tab[i] = pop - a;
        pop = a;
	}

	tab[m] = INT_MIN;

	pop = wej[0];
	for (int i = 1; i < n; i++) {
        tab[m + i] = pop - wej[i];
        pop = wej[i];
	}
	int dlug = m + n;

	ps[0] = -1;
	ps[1] = 0;
	for (int i = 2; i < dlug; i++) {
		int wyn = ps[i - 1];
		while (wyn >= 0 && tab[i] != tab[wyn + 1]) {
			wyn = ps[wyn];
		}
		ps[i] = wyn + 1;
	}

	int wynik = 0;
	for (int i = 1; i < dlug; i++) {
        if (ps[i] == m - 1) {
            wynik++;
        }
	}
	cout << wynik;

	return 0;
}
