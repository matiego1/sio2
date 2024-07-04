#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Pole_wej {
	int wiersz, pocz, kon;
};
struct Pole {
	int pocz, kon, id;
};

const int MAX = 1000 * 1000;
Pole_wej wej[MAX + 1];
vector<Pole> biale[MAX + 1];
vector<Pole> czarne[MAX + 1];
vector<int> kra;

int findd(int x) {
	if (kra[x] == x) return x;
	kra[x] = findd(kra[x]);
	return kra[x];
}
void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[a] = b;
}

bool da_sie_przejsc(int od_pocz, int od_kon, int do_pocz, int do_kon) {
	od_pocz--;
	od_kon++;
	return !(od_kon < do_pocz || do_kon < od_pocz);
}

int znajdz_id(vector<Pole>& pola, int poz) {
	if (pola.empty()) return -1;
	auto p = lower_bound(pola.begin(), pola.end(), poz, [](Pole& akt, int x) { return akt.pocz <= x; });
	if (p == pola.begin()) return -1;
	p--;
	if (p == pola.end()) return -1;
	if (p -> pocz <= poz && poz <= p->kon) return p->id;
	return -1;
}

void wygeneruj_polaczenia(int n, vector<Pole> (&pola)[MAX + 1]) {
	for (int i = 1; i < n; i++) {
		int indeks = 0;
		for (Pole& pole : pola[i]) {
			while (indeks < (int) pola[i + 1].size()) {
				if (!da_sie_przejsc(pole.pocz, pole.kon, pola[i + 1][indeks].pocz, pola[i + 1][indeks].kon)) {
					if (pola[i + 1][indeks].kon < pole.pocz) {
						indeks++;
						continue;
					}
					break;
				}
				unionn(pole.id, pola[i + 1][indeks].id);
				indeks++;
			}
			indeks = max(0, indeks - 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, p;
	cin >> n >> m >> p;
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		wej[i] = {a, b, c};
	}
	
	sort(wej + 1, wej + 1 + m, [](Pole_wej& a, Pole_wej& b) { return a.wiersz == b.wiersz ? (a.pocz == b.pocz ? a.kon > b.kon : a.pocz < b.pocz) : a.wiersz < b.wiersz; });
	
	// Wygeneruj czarne
	for (int i = 1; i <= m; i++) {
		Pole_wej pole = wej[i];
		
		if (czarne[pole.wiersz].empty()) {
			czarne[pole.wiersz].push_back({pole.pocz, pole.kon, -1});
			continue;
		}
		
		Pole& ost = czarne[pole.wiersz].back();
		if (pole.kon < ost.pocz) continue;
		if (ost.kon + 1 < pole.pocz) {
			czarne[pole.wiersz].push_back({pole.pocz, pole.kon, -1});
		} else {
			ost.kon = max(ost.kon, pole.kon);
		}
	}
	
	// Wygeneruj biale
	for (int i = 1; i <= n; i++) {
		if (czarne[i].empty()) {
			biale[i].push_back({1, n, -1});
			continue;
		}
		if (czarne[i].size() == 1 && czarne[i][0].pocz == 1 && czarne[i][0].kon == n) continue;
		
		int pocz = 1, j = 0;
		if (czarne[i][j].pocz == 1) {
			pocz = czarne[i][j].kon + 1;
			j++;
		}
		for (; j < (int) czarne[i].size(); j++) {
			int kon = czarne[i][j].pocz - 1;
			biale[i].push_back({pocz, kon, -1});
			pocz = czarne[i][j].kon + 1;
		}
		if (pocz <= n) {
			biale[i].push_back({pocz, n, -1});
		}
	}

	// Wygeneruj indeksy	
	int indeks = 0;
	for (int i = 1; i <= n; i++) {
		for (Pole& pole : biale[i]) {
			pole.id = (++indeks);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (Pole& pole : czarne[i]) {
			pole.id = (++indeks);
		}
	}
	
	// Wygeneruj F&U
	for (int i = 0; i <= indeks; i++) kra.push_back(i);
	wygeneruj_polaczenia(n, biale);
	wygeneruj_polaczenia(n, czarne);
	
	// Zapytania
	for (int i = 1; i <= p; i++) {
		int w1, k1, w2, k2;
		cin >> w1 >> k1 >> w2 >> k2;
		
		int id1 = znajdz_id(biale[w1], k1), id2;
		if (id1 == -1) {
			id1 = znajdz_id(czarne[w1], k1);
			id2 = znajdz_id(czarne[w2], k2);
		} else {
			id2 = znajdz_id(biale[w2], k2);
		}
		if (id2 == -1) {
			cout << "NIE\n";
			continue;
		}
		
		cout << (findd(id1) == findd(id2) ? "TAK" : "NIE") << "\n";
	}

	return 0;
}