#include <iostream>
#include <vector>
using namespace std;

struct Plama {
	int v, zasieg, kolor;
};
Plama make_plama(int v, int zasieg, int kolor) {
	return {v, zasieg, kolor};
}

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
Plama plamy[MAX + 1];
int wynik[MAX + 1];
int maks_zasieg[MAX + 1];

void dfs(int v, int zasieg, int kolor) {
	if (maks_zasieg[v] >= zasieg) return;
	maks_zasieg[v] = zasieg;
	
	if (wynik[v] == 0) {
		wynik[v] = kolor;
	}
	
	zasieg--;
	if (zasieg <= 0) return;
	
	for (int u : graf[v]) {
		dfs(u, zasieg, kolor);
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
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		plamy[i] = make_plama(a, b, c);
	}
	
	for (int i = q; i >= 1; i--) {
		dfs(plamy[i].v, plamy[i].zasieg + 1, plamy[i].kolor);
	}
	
	for (int i = 1; i <= n; i++) {
		cout << wynik[i] << "\n";
	}

	return 0;
}

