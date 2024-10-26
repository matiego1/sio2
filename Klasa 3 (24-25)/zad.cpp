#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Krawedz {
	int v, u, waga, indeks;
};

const int MAX = 300 * 1000;
Krawedz krawedzie[MAX + 1];
int kra[MAX + 1];
int wynik[MAX + 1];

int findd(int x) {
	if (x == kra[x]) return x;
	return (kra[x] = findd(kra[x]));
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[a] = b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = {a, b, c, i};
	}
	
	sort(krawedzie + 1, krawedzie + 1 + m, [](Krawedz& k1, Krawedz& k2) { return k1.waga < k2.waga; });
	
	ll koszt = 0;
	int indeks = 0;
	for (int i = 1; i <= m; i++) {
		Krawedz& k = krawedzie[i];
		if (findd(k.u) == findd(k.v)) continue;
		unionn(k.u, k.v);
		wynik[indeks++] = k.indeks;
		koszt += k.waga;
	}
	
	for (int i = 2; i <= n; i++) {
		if (findd(i) != findd(1)) {
			cout << "NIE";
			return 0;
		}
	}
	
	cout << "TAK\n";
	cout << koszt << "\n";
	for (int i = 0; i < indeks; i++) {
		cout << wynik[i] << "\n";
	}

	return 0;
}
