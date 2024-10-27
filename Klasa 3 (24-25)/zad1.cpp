#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
int kra[MAX + 1];
vector<int> grupy[MAX + 1];
para krawedzie[MAX + 1];
vector<para> zapytania[MAX + 1];
int wyniki[MAX + 1];

int findd(int x) {
	if (x == kra[x]) return x;
	return (kra[x] = findd(kra[x]));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q;
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
		grupy[i].push_back(i);
	}
	
	for (int i = 1; i <= m; i++) {
		cin >> krawedzie[i].first >> krawedzie[i].second;
	}
	
	for (int i = 1; i <= q; i++) {
		int a, b;
		cin >> a >> b;
		zapytania[a].push_back({b, i});
		zapytania[b].push_back({a, i});
		wyniki[i] = (a == b ? 0 : -1);
	}
	
	for (int i = 1; i <= m; i++) {
		int a = findd(krawedzie[i].first);
		int b = findd(krawedzie[i].second);
		if (a == b) continue;
		
		if (grupy[b].size() > grupy[a].size()) swap(a, b);
		kra[b] = a;
		for (int x : grupy[b]) {
			grupy[a].push_back(x);
			
			for (para p : zapytania[x]) {
				if (wyniki[p.second] != -1) continue;
				if (findd(x) != findd(p.first)) continue;
				wyniki[p.second] = i;
			}
		}
	}
	
	for (int i = 1; i <= q; i++) {
		if (wyniki[i] == -1) {
			cout << "+oo\n";
		} else {
			cout << wyniki[i] << "\n";
		}
	}

	return 0;
}


