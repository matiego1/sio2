#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1505 * 1505;
const int K = 22;
int graf[MAX];
vector<int> graf2[MAX];
int glebokosc[MAX];
para order[MAX];
int korzen[MAX];
int skladowa[MAX];
bool cykl[MAX];
int rozmiar[MAX];
int indeks[MAX];
int skok[MAX];
vector<int> sciezka;
int t = 0;

int n, m;

int f(int x, int y) {
	return (x - 1) * m + y;
}

void ruch(int& a, int& b, char k) {
	if (k == '<') b--;
	else if (k == '>') b++;
	else if (k == '^') a--;
	else if (k == 'v') a++;
}

void dfs(int v, int sklad, int kor) {
	order[v].first = ++t;
	if (v != kor) skladowa[v] = sklad;
	korzen[v] = kor;
	for (int u : graf2[v]) {
		if (cykl[u]) continue;
		glebokosc[u] = glebokosc[v] + 1;
		dfs(u, sklad, kor);
	}
	order[v].second = t;
}

bool czy_poddrzewo(int a, int b) {
	return order[a].first <= order[b].first && order[b].first <= order[a].second;
}

bool czy_da_sie_dojsc(int pocz, int kon) {
	int sklad_pocz = skladowa[pocz];
	int sklad_kon = skladowa[kon];
	
	if (sklad_pocz == sklad_kon) {
		if (cykl[pocz]) return true;
		return czy_poddrzewo(kon, pocz);
	}
	
	return skladowa[korzen[pocz]] == skladowa[kon];
}

int odleglosc_cykl(int pocz, int kon) {
	int roz = rozmiar[skladowa[pocz]];
	pocz = indeks[pocz];
	kon = indeks[kon];
	
	if (pocz >= kon) return pocz - kon;
	return roz - kon + pocz;
}

int odleglosc(int pocz, int kon) {
	int sklad_pocz = skladowa[pocz];
	int sklad_kon = skladowa[kon];

	if (sklad_pocz == sklad_kon) {
		if (cykl[pocz]) return odleglosc_cykl(pocz, kon);
		return abs(glebokosc[pocz] - glebokosc[kon]);
	}
	
	int kor1 = korzen[pocz];
	if (cykl[pocz]) kor1 = pocz;
	int kor2 = korzen[kon];
	if (cykl[kon]) kor2 = kon;
	return odleglosc_cykl(kor1, kor2) + glebokosc[pocz] + glebokosc[kon];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int a = f(i, j);
			
			char c;
			cin >> c;
			
			int b = 0;
			if (c == '<' && j > 1) b = f(i, j - 1);
			else if (c == '>' && j < m) b = f(i, j + 1);
			else if (c == 'v' && i < n) b = f(i + 1, j);
			else if (c == '^' && i > 1) b = f(i - 1, j);
			
			graf[a] = b;
			graf2[b].push_back(a);
			skok[a] = b;
		}
	}
	
	for (int k = 1; k <= K; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int v = f(i, j);
				skok[v] = skok[skok[v]];
			}
		}
	}
	
	int sklad = 0;
	for (int u : graf2[0]) {
		sklad++;
		skladowa[u] = sklad;
		glebokosc[u] = 1;
		dfs(u, sklad, u);
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int v = f(i, j);
			if (skladowa[v]) continue;
			
			sklad++;
			sciezka.clear();
			
			while (skladowa[v] == 0) {
				skladowa[v] = sklad;
				sciezka.push_back(v);
				v = graf[v];
			}
			
			if (skladowa[v] == sklad) {
				while (true) {
					int u = sciezka.back();
					cykl[u] = true;
					rozmiar[sklad]++;
					indeks[u] = rozmiar[sklad];
					
					if (sciezka.back() == v) break;
					sciezka.pop_back();
				}
				
				if (sciezka.size() <= 1) continue;
				
				sklad++;
			}
			
			dfs(v, sklad, v);
		}
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int a, b, c, d;
		char k;
		cin >> a >> b >> c >> d >> k;
		
		int start = f(a, b);
		int kraw_pocz = f(c, d);
		ruch(c, d, k);
		int kraw_kon = f(c, d);
		if (!(1 <= c && c <= n) || !(1 <= d && d <= m)) kraw_kon = 0;
		
		if (!czy_da_sie_dojsc(start, kraw_pocz)) {
			if (skok[start] != 0) {
				cout << "0\n";
				continue;
			}
			cout << glebokosc[start] << "\n";
			
			continue;
		}
		
		int wynik = odleglosc(start, kraw_pocz) + 1;
		
		if (czy_da_sie_dojsc(kraw_kon, kraw_pocz)) {
			cout << "0\n";
			continue;
		}
		
		if (skok[kraw_kon] != 0) {
			cout << "0\n";
			continue;
		}
		wynik += glebokosc[kraw_kon];
		
		cout << wynik << "\n";
	}

	return 0;
}
