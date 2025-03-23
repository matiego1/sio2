#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> para;

const int X = 330;
const int MAX = 100 * 1000;

int wynik[MAX + 1];
vector<para> skoki[X];
int zmiany[MAX + 2];
int pos_wynik[MAX + 1];

void brut1(int a, int l, int d) {
	int koniec = a + (l - 1) * d;
	while (a <= koniec) {
		wynik[a]++;
		a += d;
	}
}

void brut2(int n) {
	for (int i = 1; i < X; i++) {
		if (skoki[i].empty()) continue;
		
		for (para p : skoki[i]) {
			zmiany[p.first]++;
			zmiany[min(MAX + 1, p.first + p.second * i)]--;
		}
		
		for (int j = 1; j <= n; j++) {
			pos_wynik[j] = pos_wynik[max(0, j - i)] + zmiany[j];
			wynik[j] += pos_wynik[j];
			zmiany[j] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= k; i++) {
		int a, l, d;
		cin >> a >> l >> d;
		
		if (d >= X) {
			brut1(a, l, d);
		} else {
			skoki[d].push_back({a, l});
		}
	}
	
	brut2(n);
	
	for (int i = 1; i <= n; i++) {
		cout << wynik[i] << " ";
	}

	return 0;
}