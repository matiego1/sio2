#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

struct Tama {
	int a, b;
	int wysokosc;
};
struct Zbior {
	ll wynik;
	int maxH;
};

const int MOD = 1000 * 1000 * 1000 + 7;

vector<Tama> tamy;
vector<Zbior> zbiory;
vector<int> kra;
int m, n;

int indeks(para punkt) {
	return (punkt.first - 1) * m + punkt.second - 1;
}

int findd(int x) {
	if (x == kra[x]) return x;
	kra[x] = findd(kra[x]);
	return kra[x];
}

void unionn(int a, int b, int h) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	
	zbiory[b].wynik = (((zbiory[b].wynik + h - zbiory[b].maxH) % MOD) * ((zbiory[a].wynik + h - zbiory[a].maxH) % MOD)) % MOD;
	zbiory[b].maxH = h;
	kra[a] = b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int H;
	cin >> m >> n >> H;
	
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= m; y++) {
			zbiory.push_back({1, 0});
			kra.push_back(zbiory.size() - 1);
		}
	}
	
	if (n > 1) {
		for (int y = 1; y <= m; y++) {
			for (int x = 1; x < n; x++) {
				int h;
				cin >> h;
				tamy.push_back({indeks({x, y}), indeks({x + 1, y}), h});
			}
		}
	}
	if (m > 1) {
		for (int y = 1; y < m; y++) {
			for (int x = 1; x <= n; x++) {
				int h;
				cin >> h;
				tamy.push_back({indeks({x, y}), indeks({x, y + 1}), h});
			}
		}
	}
	
	sort(tamy.begin(), tamy.end(), [](Tama& a, Tama& b) { return a.wysokosc < b.wysokosc; });
	
	for (Tama t : tamy) {
		unionn(t.a, t.b, t.wysokosc);
	}
	
	int ost = findd(tamy[0].a);
	cout << (zbiory[ost].wynik + H - zbiory[ost].maxH) % MOD;

	return 0;
}