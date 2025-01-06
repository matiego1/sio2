#include "glolib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
int ojciec[MAX + 1];
bool wziete[MAX + 1];
int wskaznik[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n = daj_n();
	
	for (int i = 2; i <= n; i++) {
		int v = daj_przelozonego(i);
		graf[v].push_back(i);
		ojciec[i] = v;
	}
	
	int v = 1;
	wziete[v] = true;
	while (true) {
		while (graf[v].size()) {
			while (wziete[graf[v][wskaznik[v]]]) wskaznik[v]++;
			v = graf[v][wskaznik[v]];
			wziete[v] = true;;
		}
		v = ruch(v);
		while (!wziete[v]) {
			wziete[v] = true;
			v = ojciec[v];
		}
	}

	return 0;
}
