#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
int gleb[MAX + 1];

int dfs(int v, int p, int maks_odleg) {
	int wynik = 0;
	gleb[v] = 1;
	for (int u : graf[v]) {
		if (u == p) continue;
		wynik += dfs(u, v, maks_odleg);
		gleb[v] = max(gleb[v], gleb[u] + 1);
	}
	
	if (gleb[v] < maks_odleg) return wynik;
	if (v == 1) return wynik;
	if (p == 1) return wynik;
	gleb[v] = 0;
	wynik++;
	return wynik;
}

bool sprawdz(int k, int maks_odleg) {
	return dfs(1, 1, maks_odleg) <= k;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	if (n == 1) {
		cout << 0;
		return 0;
	}
	
	int pocz = 1, kon = n;
	while (pocz < kon) {
		int srodek = (pocz + kon) / 2;
		if (sprawdz(k, srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	cout << pocz;

	return 0;
}
