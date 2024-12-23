#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 2000 * 1000;
string wej[MAX + 1];
vector<int> ps[MAX + 1];
string tab[MAX + 1];

void kmp(int indeks) {
	ps[indeks].resize(wej[indeks].length() + 1);
	ps[indeks][0] = -1;
	ps[indeks][1] = 0;
	for (int i = 2; i <= (int) wej[indeks].length(); i++) {
		int wyn = ps[indeks][i - 1];
		while (wyn >= 0 && wej[indeks][i - 1] != wej[indeks][wyn]) {
			wyn = ps[indeks][wyn];
		}
		ps[indeks][i] = wyn + 1;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i] >> wej[i];
	}
	
	for (int i = 1; i <= n; i++) {
		kmp(i);
	}
	
	for (int i = 1; i <= n; i++) {
		int k = (int) wej[i].size();
		int p = ps[i][wej[i].size()];
		if (k % (k - p) == 0) {
			tab[i] = wej[i].substr(0, k - p);
		} else {
			tab[i] = wej[i];
		}
	}
	
	sort(tab + 1, tab + 1 + n);
	
	ll wynik = 0, akt = 1;
	for (int i = 2; i <= n; i++) {
		if (tab[i] != tab[i - 1]) {
			wynik += akt * (akt - 1) / 2;
			akt = 0;
		}
		akt++;
	}
	wynik += akt * (akt - 1) / 2;
	cout << 2 * wynik + n;

	return 0;
}

