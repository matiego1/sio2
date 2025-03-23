#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

// https://stackoverflow.com/questions/32685540/why-cant-i-compile-an-unordered-map-with-a-pair-as-key
struct pair_hash {
    template <class T1, class T2> size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);  
    }
};
typedef unordered_map<para, vector<int>, pair_hash> Mapa1;
typedef unordered_map<int, int> Mapa2;

const ll MOD = 1000 * 1000 * 1000 + 7;
const ll P = 100019;
const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
int wej[MAX + 1];
bool czy_centroid[MAX + 1];
int rozmiar[MAX + 1];
ll potega_P[MAX + 1];
bool wynik[MAX + 1];

int n, k;
ll hash_wszystkich = 0;

void dfs_rozmiar(int v, int p) {
	rozmiar[v] = 1;
	for (int u : graf[v]) {
		if (u == p) continue;
		if (czy_centroid[u]) continue;
		dfs_rozmiar(u, v);
		rozmiar[v] += rozmiar[u];
	}
}

int dfs_centroid(int v, int p, int roz) {
	for (int u : graf[v]) {
		if (u == p) continue;
		if (czy_centroid[u]) continue;
		if (rozmiar[u] > roz / 2) {
			return dfs_centroid(u, v, roz);
		}
	}
	return v;
}

void dfs_ojciec(int v, int p, Mapa2& ojciec) {
	ojciec[v] = p;
	for (int u : graf[v]) {
		if (u == p) continue;
		if (czy_centroid[u]) continue;
		dfs_ojciec(u, v, ojciec);
	}
}

void dfs_wynik(int v, Mapa2& ojciec) {
	wynik[v] = true;
	int p = ojciec[v];
	if (v == p) return;
	ojciec[v] = v;
	dfs_wynik(p, ojciec);
}

void dfs_wierzcholki(int v, int p, int gleb, ll hash, Mapa1& mapa, Mapa2& ojciec) {
	hash = (hash + potega_P[wej[v]]) % MOD;
	
	ll brakujaca_gleb = k - 1 - gleb;
	ll brakujacy_hash = (hash_wszystkich - hash + MOD) % MOD;
	para klucz = {brakujaca_gleb, brakujacy_hash};
	
	if (mapa.find(klucz) != mapa.end()) {
		for (int x : mapa[klucz]) {
			dfs_wynik(x, ojciec);
		}
		dfs_wynik(v, ojciec);
		mapa[klucz].clear();
	}
	
	for (int u : graf[v]) {
		if (u == p) continue;
		if (czy_centroid[u]) continue;
		dfs_wierzcholki(u, v, gleb + 1, hash, mapa, ojciec);
	}
}

void dfs_mapa(int v, int p, int gleb, ll hash, Mapa1& mapa) {
	hash = (hash + potega_P[wej[v]]) % MOD;
	
	mapa[{gleb, hash}].push_back(v);
	
	for (int u : graf[v]) {
		if (u == p) continue;
		if (czy_centroid[u]) continue;
		dfs_mapa(u, v, gleb + 1, hash, mapa);
	}
}

void dfs(int v, int p) {
	dfs_rozmiar(v, p);
	
	int centroid = dfs_centroid(v, p, rozmiar[v]);
	czy_centroid[centroid] = true;
	
	Mapa2 ojciec;
	dfs_ojciec(centroid, centroid, ojciec);
	
	Mapa1 mapa;
	mapa[{0, potega_P[wej[centroid]]}].push_back(centroid);
	
	for (int u : graf[centroid]) {
		if (czy_centroid[u]) continue;
		
		dfs_wierzcholki(u, centroid, 1, 0, mapa, ojciec);
		dfs_mapa(u, centroid, 1, potega_P[wej[centroid]], mapa);
		
		dfs(u, centroid);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int q;
	cin >> n >> k >> q;
	
	potega_P[0] = 1;
	for (int i = 1; i <= k; i++) {
		potega_P[i] = potega_P[i - 1] * P % MOD;
		hash_wszystkich = (hash_wszystkich + potega_P[i]) % MOD;
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);		
	}
	
	dfs(1, 1);
	
	while (q--) {
		int v;
		cin >> v;
		cout << (wynik[v] ? "TAK" : "NIE") << "\n";
	}

	return 0;
}