#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;

int wej[MAX + 1];
int wej_kopia[MAX + 1];
para pom[MAX + 1];
map<int, int> mapa;

struct Wavelet {
	int mini, maks;
	Wavelet* lewy;
	Wavelet* prawy;
	vector<int> pref;
	
	Wavelet(int* pocz, int* kon, int a, int b) {
		mini = a, maks = b;
		if (mini == maks || pocz >= kon) return;
		
		int srodek = (mini + maks) / 2;
		auto f = [srodek](int x) {
			return x <= srodek;
		};
		
		pref.push_back(0);
		for (auto it = pocz; it != kon; it++) {
			pref.push_back(pref.back() + f(*it));
		}
		
		auto pivot = stable_partition(pocz, kon, f);
		lewy = new Wavelet(pocz, pivot, mini, srodek);
		prawy = new Wavelet(pivot, kon, srodek + 1, maks);
	}
	
	int query(int l, int r, int k) {
		if (mini == maks) return mini;
		
		int po_lewej = pref[r] - pref[l - 1];
		if (k <= po_lewej) {
			return lewy->query(pref[l - 1] + 1, pref[r], k);
		} else {
			return prawy->query(l - pref[l - 1], r - pref[r], k - po_lewej);
		}
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	for (int i = 1; i <= n; i++) {
		pom[i] = {wej[i], i};
	}
	sort(pom + 1, pom + 1 + n);
	int wart = 0;
	pom[0].first = -5;
	for (int i = 1; i <= n; i++) {
		if (pom[i].first != pom[i - 1].first) wart++;
		mapa[wart] = wej[pom[i].second];
		wej_kopia[pom[i].second] = wart;
	}
	
	Wavelet tree(wej_kopia + 1, wej_kopia + 1 + n, 1, MAX + 5);
	while (q--) {
		int l, r, m, k;
		cin >> l >> r >> m >> k;
		
		int p = l + k + m - 2;
		if (p > r) {
			cout << mapa[tree.query(l, r, k)] << "\n";
		} else {
			cout << min(wej[p], mapa[tree.query(l, p, k)]) << "\n";
		}
	}
	
	return 0;
}

