#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, ll> para;

const int MAX = 1000 * 1000;
const ll INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
ll wej[MAX + 1];

struct Zbior {
	ll suma;
	set<para> zbior;
	
	void clear(int n, int kier) {
		zbior.clear();
		if (kier == 1) {
			zbior.insert({1, 0});
			zbior.insert({n + 1, INF});
		} else {
			zbior.insert({-n, 0});
			zbior.insert({0, INF});
		}
		suma = 0;
	}
	
	void dodaj(int i, ll wart) {
		auto x = zbior.upper_bound({i, INF});
		x--;
		
		if (x->second >= wart) return;
		
		suma -= x->second * (next(x)->first - i);
		suma += wart * (next(x)->first - i);
		
		if (x->first == i) {
			zbior.erase(x);
		}
		x = zbior.insert({i, wart}).first;
		
		while (next(x)->second <= wart) {
			int ile = next(next(x))->first - next(x)->first;
			suma -= next(x)->second * ile;
			suma += wart * ile;
			zbior.erase(next(x));
		}
	}
};
Zbior f, g;

void rozwiaz() {
	int n;
	cin >> n;
	
	ll suma = 0, maks = 0;
	
	f.clear(n, 1);
	g.clear(n, -1);
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		
		suma += wej[i];
		maks = max(maks, wej[i]);
		
		f.dodaj(i, wej[i]);
		g.dodaj(-i, wej[i]);
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b;
		cin >> a >> b;
		
		wej[a] += b;
		suma += b;
		maks = max(maks, wej[a]);
		
		f.dodaj(a, wej[a]);
		g.dodaj(-a, wej[a]);
		
		cout << f.suma + g.suma - maks * n - suma << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	
	while (t--) {
		rozwiaz();
	}

	return 0;
}

