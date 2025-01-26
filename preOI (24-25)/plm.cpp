#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Krawedz {
	int v, u, koszt;
};

const int MAX = 500 * 1000;
Krawedz krawedzie[MAX + 1];
vector<int> graf[MAX + 1];
int kra[MAX + 1];
int wynik[MAX + 1];

int findd(int x) {
	if (kra[x] == x) return x;
	return (kra[x] = findd(kra[x]));
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[a] = b;
}

void dfs(int v, int p, int typ) {
	wynik[v] = typ;
	typ ^= 1;
	
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs(u, v, typ);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) kra[i] = i;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, c};
	}
	
	sort(krawedzie + 1, krawedzie + 1 + m, [](Krawedz& k1, Krawedz& k2) {
		return k1.koszt < k2.koszt;
	});
	
	for (int i = 1; i <= m; i++) {
		Krawedz& k = krawedzie[i];
		
		if (findd(k.v) == findd(k.u)) continue;
		unionn(k.v, k.u);
		
		graf[k.v].push_back(k.u);
		graf[k.u].push_back(k.v);
	}
	
	dfs(1, 1, 0);
	
	for (int i = 1; i <= n; i++) {
		cout << (wynik[i] ? 'M' : 'B');
	}

	return 0;
}

