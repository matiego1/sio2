#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int INF = 2000 * 1000 * 1000;
const int MAX_N = 200;
const int MAX = 20 * 1000;
int b[MAX_N + 1];
int c[MAX_N + 1];
int dp[MAX + 1];
int tab[MAX + 1];
int wynik[MAX_N + 1];
int ilosci[MAX_N + 1][MAX + 1];


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	int k;
	cin >> k;
	
	for (int i = 1; i <= k; i++) dp[i] = INF;
	for (int i = 1; i <= n; i++) {
		for (int r = 0; r <= b[i] - 1; r++) {
			deque<int> q;
			int ilosc = 0;
			while (r + ilosc * b[i] <= k) {
				tab[ilosc] = dp[r + ilosc * b[i]] - ilosc;
				while (q.size() && tab[q.back()] > tab[ilosc]) q.pop_back();
				q.push_back(ilosc);
				dp[r + ilosc * b[i]] = tab[q.front()] + ilosc;
				ilosci[i][r + ilosc * b[i]] = ilosc - q.front();
				if (q.front() == ilosc - c[i]) q.pop_front();
				ilosc++;
			}
		}
	}
	
	int suma = 0;
	for (int i = n; i >= 1; i--) {
		wynik[i] = ilosci[i][k];
		suma += ilosci[i][k];
		k -= ilosci[i][k] * b[i];
	}
	
	cout << suma << "\n";
	for (int i = 1; i <= n; i++) cout << wynik[i] << " ";

	return 0;
}

