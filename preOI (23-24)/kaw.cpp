#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

struct Sasiad {
	int v, jednorazowy, dzienny;
};

const int MAX = 2 * 1000 * 1000;
vector<Sasiad> graf[MAX + 1];
int prz[MAX + 1];
int dp[MAX + 1];
int gleb[MAX + 2];
int lca[MAX];
int kra[MAX + 1];
int rozmiar[MAX + 1];
int n;

int findd(int a) {
	if (a == kra[a]) return a;
	kra[a] = findd(kra[a]);
	return kra[a];
}
void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	if (rozmiar[a] < rozmiar[b]) swap(a, b);
	kra[b] = a;
	rozmiar[a] += rozmiar[b];
}

void dfs_1(int v, int ojciec) {
	prz[v] = v;
	for (Sasiad& u : graf[v]) {
		if (u.v != ojciec) {
			gleb[u.v] = gleb[v] + 1;
			dfs_1(u.v, v);
			unionn(v, u.v);
			prz[findd(v)] = v;
		}
	}
	if (gleb[v + 1] > 0) {
		lca[v] = prz[findd(v + 1)];
	}
	if (gleb[v - 1] > 0) {
		lca[v - 1] = prz[findd(v - 1)];
	}
}

void dfs_2(int v, int ojciec) {
	for (Sasiad& u : graf[v]) {
		if (u.v != ojciec) {
			dfs_2(u.v, v);
			dp[v] += dp[u.v];
		}
	}
}

int wczytaj_int() {
	int x = 0, znak;
	while ((znak = getchar()) != '\n' && znak != ' ') {
		x = x * 10 + (znak - '0');
	}
	return x;
}

int main() {
	n = wczytaj_int();
	
	for (int i = 1; i < n; i++) {
		kra[i] = i;
		int a = wczytaj_int(), b = wczytaj_int(), c = wczytaj_int(), d = wczytaj_int();
		
		graf[a].push_back({b, c, d});
		graf[b].push_back({a, c, d});
	}
	kra[n] = n;
	
	gleb[1] = 1;
	dfs_1(1, 1);
	
	for (int i = 1; i < n; i++) {
		dp[i]++;
		dp[i + 1]++;
		dp[lca[i]] -= 2;
	}
	
	dfs_2(1, 1);
	
	ll wynik = 0;
	for (int i = 1; i <= n; i++) {
		for (Sasiad& u : graf[i]) {
			if (gleb[u.v] < gleb[i]) continue;
			wynik += min((ll) dp[u.v] * u.jednorazowy, (ll) u.dzienny);
		}
	}
	
	printf("%lld", wynik);

	return 0;
}
