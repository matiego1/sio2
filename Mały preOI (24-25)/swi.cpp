#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
para wej[MAX + 1];
para tab[2 * MAX + 1];
bool wziete[MAX + 1];
vector<int> swiszcze;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i].first >> wej[i].second;
		wej[i].second = wej[i].first / wej[i].second + 1;
	}
	
	for (int i = 1; i <= n; i++) {
		tab[2 * i - 1] = {wej[i].second, -i};
		tab[2 * i] = {wej[i].first, i};
	}
	
	sort(tab + 1, tab + 1 + 2 * n);
	
	int wynik = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (tab[i].second > 0) {
			if (wziete[tab[i].second]) continue;
			wynik++;
			for (int x : swiszcze) {
				wziete[x] = true;
			}
			swiszcze.clear();
		} else {
			swiszcze.push_back(-tab[i].second);
		}
	}
	
	cout << wynik;
	
	return 0;
}
