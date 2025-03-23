#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int PUNKT = 1;
const int ZAPYT = 2;
const int KON = 3;
const int POCZ = 4;
struct Wydarz {
	int x, typ, indeks, y1, y2 = -1;
};
bool operator<(Wydarz& w1, Wydarz& w2) {
	return tie(w1.x, w1.typ, w1.indeks, w1.y1, w1.y2) < tie(w2.x, w2.typ, w2.indeks, w2.y1, w2.y2);
}

const int MAX = 1000 * 1000;
Wydarz wydarz[4 * MAX + 10];
para punkty[MAX + 1];
pair<para, para> pola[MAX + 1];
vector<int> graf[MAX + 1];
bool odwie[MAX + 1];
int odleg[MAX + 1];
set<para> zbior;
queue<int> q;

int ustaw_wydarz(int n, int m, bool zamien) {
	int rozmiar = 0;
	
	for (int i = 1; i <= m; i++) {
		if (zamien) swap(punkty[i].first, punkty[i].second);
		wydarz[++rozmiar] = {punkty[i].first, PUNKT, i, punkty[i].second};
	}
	
	for (int i = 1; i <= n; i++) {
		if (zamien) swap(pola[i].first, pola[i].second);
		wydarz[++rozmiar] = {pola[i].first.first, ZAPYT, i, pola[i].second.first, pola[i].second.second};
		wydarz[++rozmiar] = {pola[i].first.first, POCZ, i, pola[i].second.first, pola[i].second.second};
		wydarz[++rozmiar] = {pola[i].first.second, KON, i, pola[i].second.first, pola[i].second.second};
	}
	
	return rozmiar;
}

para rozwiaz(int n, int m, bool zamien) {
	int rozmiar = ustaw_wydarz(n, m, zamien);
	
	sort(wydarz + 1, wydarz + 1 + rozmiar);
	
	int start = -1, meta = -1;
	for (int i = 1; i <= rozmiar; i++) {
		Wydarz& w = wydarz[i];
		if (w.typ == PUNKT) {
			int indeks = zbior.upper_bound({w.y1, 0})->second;
			
			if (w.indeks == 1) {
				start = indeks;
			} else if (w.indeks == 2) {
				meta = indeks;
			} else {
				odwie[indeks] = true;
			}
		} else if (w.typ == ZAPYT) {
			auto pocz = zbior.upper_bound({w.y1, 0});
			auto kon = zbior.lower_bound({w.y2, 0});
			
			for (; pocz != zbior.end() && pocz != next(kon); pocz++) {
				if (pocz->first == w.y1) continue;
				
				graf[w.indeks].push_back(pocz->second);
				graf[pocz->second].push_back(w.indeks);
			}
		} else if (w.typ == POCZ) {
			zbior.insert({w.y2, w.indeks});
		} else if (w.typ == KON) {
			zbior.erase({w.y2, w.indeks});
		}
	}
	
	return {start, meta};
}

void bfs(int start) {
	odleg[start] = 1;
	odwie[start] = true;
	q.push(start);
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		for (int u : graf[v]) {
			if (odwie[u]) continue;
			odleg[u] = odleg[v] + 1;
			odwie[u] = true;
			q.push(u);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int w, h, n, m;
	cin >> w >> h >> n >> m;
	
	cin >> punkty[1].first >> punkty[1].second;
	cin >> punkty[2].first >> punkty[2].second;
	
	for (int i = 1; i <= n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		
		pola[i] = {{x1, x2}, {y1, y2}};
	}
	
	m += 2;
	for (int i = 3; i <= m; i++) {
		cin >> punkty[i].first >> punkty[i].second;
	}
	
	// od lewej do prawej
	para start_meta = rozwiaz(n, m, false);
	
	// od dolu do gory
	rozwiaz(n, m, true);
	
	bfs(start_meta.first);
	
	cout << odleg[start_meta.second];

	return 0;
}

