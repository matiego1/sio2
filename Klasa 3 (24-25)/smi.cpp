#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
multiset<int> graf[MAX + 1];
bool odwie[MAX + 1];
vector<int> wynik[MAX + 1];
vector<vector<int>> wyj;
bool uzyte[MAX + 1];

void dfs(int v, int indeks) {
	odwie[v] = true;
	while (graf[v].size()) {
		int u = *graf[v].begin();
		graf[v].erase(u);
		graf[u].erase(v);
		dfs(u, indeks);
		wynik[indeks].push_back(v);
	}
}

void generuj_wyj(vector<int>& tab) {
	int indeks = (int) wyj.size();
	wyj.push_back({});
	for (int i = 0; i < (int) tab.size(); i++) {
		if (uzyte[tab[i]]) {
			int akt = (int) wyj.size();
			wyj.push_back({});
			
			int x = -1;
			while (x != tab[i]) {
				x = wyj[indeks].back();
				wyj[akt].push_back(x);
				uzyte[x] = false;
				wyj[indeks].pop_back();
			}
		}
		uzyte[tab[i]] = true;
		wyj[indeks].push_back(tab[i]);
	}
	
	for (int x : tab) uzyte[x] = false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (c == d) continue;
		graf[a].insert(b);
		graf[b].insert(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if (graf[i].size() & 1) {
			cout << "NIE";
			return 0;
		}
	}
	
	int indeks = 0;
	for (int i = 1; i <= n; i++) {
		if (odwie[i]) continue;
		indeks++;
		dfs(i, indeks);
		if (wynik[indeks].empty()) indeks--;
	}
	
	for (int i = 1; i <= n; i++) {
		if (graf[i].size()) {
			cout << "NIE";
			return 0;
		}
	}
	
	for (int i = 1; i <= indeks; i++) {
		generuj_wyj(wynik[i]);
	}
	
	cout << wyj.size() << "\n";
	for (vector<int>& v : wyj) {
		cout << v.size() << " " << v.back() << " ";
		for (int x : v) {
			cout << x << " ";
		}
		cout << "\n";
	}

	return 0;
}
