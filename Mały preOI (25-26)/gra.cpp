#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
const ld EPS = 0.0000001;
int ojciec[MAX + 1];
vector<int> graf[MAX + 1];
int dzieci[MAX + 1];
int dp[MAX + 1];
int n, k;

void dfs_dzieci(int v) {
	for (int u : graf[v]) {
		dfs_dzieci(u);
		dzieci[v] += dzieci[u] + 1;
	}
}

bool dfs(int v, ld& x) {
	dp[v] = 1;
	for (int u : graf[v]) {
		if (dfs(u, x)) return true;
		if (x * dzieci[v] < dp[u]) {
			dp[v] = dzieci[v] + 1;
		}
	}
	return dp[v] > k;
}

bool sprawdz(ld x) {
	return dfs(1, x);
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	n = wczytaj();
	k = wczytaj();
	
	for (int i = 2; i <= n; i++) {
		int a = wczytaj();
		graf[a].push_back(i);
		ojciec[i] = a;
	}
	
	dfs_dzieci(1);
	
	ld pocz = 0, kon = 1;
	
	while (abs(pocz - kon) >= EPS) {
		ld srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			pocz = srodek + EPS;
		} else {
			kon = srodek;
		}
	}
	
	if (pocz >= 1) {
		pocz = 0;
	}

	printf("%.7Lf", pocz);

	return 0;
}
