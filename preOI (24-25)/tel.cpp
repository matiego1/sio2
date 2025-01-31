#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000;
para wej[MAX * MAX + 10];
int zlicz[MAX + 1];
int ile = 0;

void zmien(int film, int wart) {
	if (wart == 1) {
		zlicz[film]++;
		if (zlicz[film] == 1) ile++;
	} else {
		zlicz[film]--;
		if (zlicz[film] == 0) ile--;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	int rozmiar = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> wej[++rozmiar].first;
			wej[rozmiar].second = i;
		}
	}
	
	sort(wej + 1, wej + 1 + rozmiar);
	
	int wynik = INT_MAX;
	int lewy = 1;
	for (int prawy = 1; prawy <= rozmiar; prawy++) {
		zmien(wej[prawy].second, 1);
		
		if (ile == n) {
			wynik = min(wynik, wej[prawy].first - wej[lewy].first + 1);
		}
		
		zmien(wej[lewy].second, -1);
		while (lewy < prawy && ile == n) {
			lewy++;
			wynik = min(wynik, wej[prawy].first - wej[lewy].first + 1);
			zmien(wej[lewy].second, -1);
		}
		zmien(wej[lewy].second, 1);
	}
	
	cout << wynik;

	return 0;
}
