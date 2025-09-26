#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int MAX = 200 * 1000;
vector<para> graf[MAX + 1];
ll rozmiar[MAX + 1];
bool czy_centroid[MAX + 1];
ll zlicz[MAX + 1];
ll zle[MAX + 1];
bool dodane[MAX + 1];
gp_hash_table<ll, ll> zle_akt;

void dfs_rozmiar(ll v, ll p) {
	rozmiar[v] = 1;
	for (para u : graf[v]) {
		if (u.first == p) continue;
		if (czy_centroid[u.first]) continue;
		dfs_rozmiar(u.first, v);
		rozmiar[v] += rozmiar[u.first];
	}
}

ll dfs_centroid(ll v, ll p, ll n) {
	for (para u : graf[v]) {
		if (u.first == p) continue;
		if (czy_centroid[u.first]) continue;
		if (rozmiar[u.first] > n / 2) {
			return dfs_centroid(u.first, v, n);
		}
	}
	return v;
}

ll dfs_wynik(ll v, ll p, ll inne) {
	ll wynik = 0;
	for (para u : graf[v]) {
		if (u.first == p) continue;
		if (czy_centroid[u.first]) continue;
		
		ll akt_inne = inne;
		if (akt_inne == -1) {
			akt_inne = rozmiar[v] - rozmiar[u.first];
			for (para x : zle_akt) {
				zle[x.first] += x.second;
			}
			zle_akt.clear();
		}
		
		zlicz[u.second]++;
		if (zlicz[u.second] == 1) {
			wynik += rozmiar[u.first] * (akt_inne - zle[u.second]);
		}
		
		bool akt_dodane = false;
		if (!dodane[u.second]) {
			zle_akt[u.second] += rozmiar[u.first];
			dodane[u.second] = true;
			akt_dodane = true;
		}
		
		wynik += dfs_wynik(u.first, v, akt_inne);
		
		if (akt_dodane) dodane[u.second] = false;
		
		zlicz[u.second]--;
	}
	return wynik;
}

void dfs_clear(ll v, ll p) {
	for (para u : graf[v]) {
		if (u.first == p) continue;
		if (czy_centroid[u.first]) continue;
		zlicz[u.second] = 0;
		zle[u.second] = 0;
		dfs_clear(u.first, v);
	}
}

ll dfs(ll v) {
	dfs_rozmiar(v, v);
	if (rozmiar[v] == 1) return 0;
	
	ll centroid = dfs_centroid(v, v, rozmiar[v]);
	czy_centroid[centroid] = true;
	dfs_rozmiar(centroid, centroid);

	dfs_clear(centroid, centroid);
	zle_akt.clear();
	
	ll wynik = dfs_wynik(centroid, centroid, -1);
	
	for (para u : graf[centroid]) {
		if (czy_centroid[u.first]) continue;
		wynik += dfs(u.first);
	}
	
	return wynik;
}

int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj('\n');
	
	for (int i = 1; i < n; i++) {
		int a = wczytaj(' '), b = wczytaj(' '), c = wczytaj('\n');
		graf[a].push_back({b, c});
		graf[b].push_back({a, c});
	}
	
	printf("%lld", dfs(1));

	return 0;
}