#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_N = 100 * 1000;
const int MAX_M = 200 * 1000;
set<para> graf[2 * MAX_N + 1];
vector<int> nieparz;
bool odwie[2 * MAX_N + 1];
int wynik[MAX_M + 1];
int znak = 1;
vector<int> poczatki;

void dfs_sklad(int v) {
	odwie[v] = true;
	if (graf[v].size() & 1) {
		nieparz.push_back(v);
	}
	for (para u : graf[v]) {
		if (odwie[u.first]) continue;
		dfs_sklad(u.first);
	}
}

void dfs(int v) {
	odwie[v] = true;
	while (graf[v].size()) {
		para u = *graf[v].begin();
		graf[v].erase(u);
		graf[u.first].erase({v, u.second});
		dfs(u.first);
		wynik[u.second] = znak;
		znak *= -1;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].insert({n + b, i});
		graf[n + b].insert({a, i});
	}
	
	for (int i = 1; i <= 2 * n; i++) {
		if (odwie[i]) continue;
		dfs_sklad(i);
		if (nieparz.empty()) {
			poczatki.push_back(i);
			continue;
		}
		while (nieparz.size() > 2) {
			int a = nieparz.back();
			nieparz.pop_back();
			int b = nieparz.back();
			nieparz.pop_back();
			graf[a].insert({b, 0});
			graf[b].insert({a, 0});
		}
		poczatki.push_back(nieparz.back());
		nieparz.clear();
	}
	
	for (int pocz : poczatki) {
		znak = 1;
		dfs(pocz);
	}
	
	cout << "TAK\n";
	for (int i = 1; i <= m; i++) {
		cout << wynik[i] << "\n";
	}

	return 0;
}

