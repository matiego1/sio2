#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000;
int wej[MAX + 1];
int pom[MAX + 1];
bool wziete[MAX + 1];
vector<para> wynik;

void stuknij(int a, int b) {
	wej[a] ^= wej[b];
	wynik.push_back({a, b});
}

void rozwiaz1(int n) {
	for (int i = 1; i <= n; i++) pom[i] = i;
	sort(pom + 1, pom + 1 + n, [](int a, int b) { return wej[a] > wej[b]; });
	
	for (int i = 1; i <= n; i++) {
		int indeks = 0;
		for (int j = 1; j <= pom[i]; j++) {
			if (!wziete[j]) indeks++;
		}
		wziete[pom[i]] = true;
 		
		for (int j = 1; j <= min(n - 1, n - i + 1); j++) {
			stuknij(j, j + 1);
		}
		for (int j = indeks - 1; j >= 2; j--) {
			stuknij(j - 1, j);
		}
		for (int j = indeks; j <= n - i; j++) {
			stuknij(j + 1, j);
		}
	}
}

void rozwiaz2(int n) {
	int kon = 0;
	for (int bit = 19; bit >= 0; bit--) {
		for (int i = 1; i < n - kon; i++) {
			int lewy = (wej[i] & (1 << bit) ? 1 : 0);
			int prawy = (wej[i + 1] & (1 << bit) ? 1 : 0);
			if (lewy == 1 && prawy == 0) {
				stuknij(i + 1, i);
				stuknij(i, i + 1);	
			} else if (lewy == 1 && prawy == 1) {
				stuknij(i, i + 1);
			}
		}
		if (wej[n - kon] & (1 << bit)) kon++;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, p;
	cin >> n >> p;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	if (p == 1) {
		rozwiaz1(n);
	} else {
		rozwiaz2(n);
	}
	
	cout << wynik.size() << "\n";
	for (para w : wynik) {
		cout << w.first << " " << w.second << "\n";
	}

	return 0;
}
