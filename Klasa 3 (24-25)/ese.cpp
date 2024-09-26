#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 100 * 1000;
int prawo[MAX];
int lewo[MAX];

int rozwiaz(int n, int m, string s1, string s2) {
	// w prawo
	for (int i = 0; i < m; i++) prawo[i] = INF;
	int i1 = 0, i2 = 0;
	while (i1 < n && i2 < m) {
		if (s1[i1] == s2[i2]) {
			prawo[i2] = i1;
			i1++;
			i2++;
		} else {
			i1++;
		}
	}
	
	// w lewo
	for (int i = 0; i < m; i++) lewo[i] = -INF;
	i1 = n - 1, i2 = m - 1;
	while (i1 >= 0 && i2 >= 0) {
		if (s1[i1] == s2[i2]) {
			lewo[i2] = i1;
			i1--;
			i2--;
		} else {
			i1--;
		}
	}
	
	if (prawo[m - 1] != INF || lewo[0] != -INF) return 0;
	
	int prawy = 0;
	for (int i = 0; i < m; i++) {
		if (prawo[i] == INF && lewo[i] == -INF) {
			prawy = i + 1;
		}
	}
	if (prawy == m) {
		for (int i = 0; i < m; i++) {
			if (prawo[i] == INF) {
				return m - i;
			}
		}
	}
	
	int wynik = (prawy > 0 ? prawy : INF);
	for (int lewy = 0; lewy < m && prawo[lewy] != INF; lewy++) {
		while (prawy < m && (prawy <= lewy || lewo[prawy] <= prawo[lewy])) {
			prawy++;
		}
		wynik = min(wynik, prawy - lewy - 1);
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	string s1, s2;
	cin >> s1 >> s2;
	
	int wynik = rozwiaz(n, m, s1, s2);
	
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	cout << min(wynik, rozwiaz(n, m, s1, s2));
	
	return 0;
}


