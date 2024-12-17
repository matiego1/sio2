#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 2000;
int wej[MAX + 2][MAX + 2];
int tab[MAX + 2];
int gora[MAX + 2];
int dol[MAX + 2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> wej[x][y];
		}
	}
	
	int wynik = 0;
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (wej[x][y] == 1) tab[y] = 0;
			else tab[y]++;
			
			dol[y] = n + 1;
			gora[y] = 0;
		}
		
		stack<int> stos;
		for (int y = 1; y <= n; y++) {
			while (stos.size() && tab[y] < tab[stos.top()]) {
				dol[stos.top()] = y;
				stos.pop();
			}
			if (stos.size()) gora[y] = stos.top();
			stos.push(y);
		}
		
		for (int y = 1; y <= n; y++) {
			wynik = max(wynik, tab[y] * (dol[y] - gora[y] - 1));
		}
	}
	cout << wynik;

	return 0;
}
