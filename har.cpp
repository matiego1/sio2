#include "harlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 20 * 1000;
const int K = 6;
const int kolory_sciezka[K] = {0, 1, 0, 0, 1, 1};
vector<para> graf[MAX];
vector<int> kolory;
queue<int> q;
bool czy_cofaj[1 << K];
bool odwie[MAX];
int ojciec[MAX];
int gleb[MAX];
int A, B;

void dfs(int v, bool sciezka, int pop_kolor) {
	if (graf[v].size() > 2) {
		if (sciezka) pop_kolor = kolory_sciezka[pop_kolor];
		int akt_kolor = pop_kolor ^ 1;
		for (para p : graf[v]) {
			if (ojciec[v] == p.first) continue;
			ojciec[p.first] = v;
			kolory[p.second] = akt_kolor;
			dfs(p.first, false, akt_kolor);
		}
	} else {
		int akt_indeks = (pop_kolor + 1) % K;
		if (!sciezka) {
			akt_indeks = pop_kolor ^ 1;
		}
		for (para p : graf[v]) {
			if (ojciec[v] == p.first) continue;
			ojciec[p.first] = v;
			kolory[p.second] = kolory_sciezka[akt_indeks];
			dfs(p.first, true, akt_indeks);
		}
	}
}

vector<int> Pomaluj(int n, int m, int A0, int B0, vector<int> U, vector<int> V) {
	A = A0;
	B = B0;
	
	kolory.resize(m);
	for (int i = 0; i < m; i++) {
		graf[U[i]].push_back({V[i], i});
		graf[V[i]].push_back({U[i], i});
	}
	
	if (B == 0) {
		q.push(0);
		odwie[0] = true;
		
		while (q.size()) {
			int v = q.front();
			q.pop();
			
			for (para p : graf[v]) {
				if (ojciec[v] == p.first) continue;
				if (odwie[p.first]) {
					kolory[p.second] = min(gleb[v], gleb[p.first]) % 3;
					continue;
				}
				
				gleb[p.first] = gleb[v] + 1;
				ojciec[p.first] = v;
				odwie[p.first] = true;
				kolory[p.second] = gleb[v] % 3;
				
				q.push(p.first);
			}
		}
	} else {
		dfs(0, false, 1);
	}
	
	return kolory;
}

void Init(int A0, int B0) {
	czy_cofaj[0b10011] = true;
	czy_cofaj[0b00101] = false;
	czy_cofaj[0b00110] = true;
	czy_cofaj[0b10010] = false;
	czy_cofaj[0b11001] = false;
	czy_cofaj[0b11010] = true;
	czy_cofaj[0b10100] = true;
	czy_cofaj[0b10110] = false;
	czy_cofaj[0b10011] = true;
	
	A = A0;
	B = B0;
}

bool pierwsze = true;
bool szukam_kierunku = false;
int dystans = 0;
int pop_kraw = -1;
int sciezka = 0;

int Rusz(vector<int> y) {
	if (B == 0) {
		if (y[0] && y[1]) return 0;
		if (y[1] && y[2]) return 1;
		if (y[2] && y[0]) return 2;
		if (y[0]) return 0;
		if (y[1]) return 1;
		return 2;
	}
	
	if (pierwsze) {
		pierwsze = false;
		// lisc
		if (y[0] == 1 && y[1] == 0) return (pop_kraw = 0);
		if (y[0] == 0 && y[1] == 1) return (pop_kraw = 1);
		// rozgalezienie
		if (y[0] == 1 && y[1] > 1) return (pop_kraw = 0);
		if (y[0] > 1 && y[1] == 1) return (pop_kraw = 1);
		
		szukam_kierunku = true;
		dystans++;
		
		for (int i = 1; i <= y[1]; i++) sciezka = (sciezka << 1) | 1;
		for (int i = 1; i <= y[0]; i++) sciezka = (sciezka << 1);
		
		if (y[0]) return (pop_kraw = 0);
		if (y[1]) return (pop_kraw = 1);
		return -5;
	}
	
	if (szukam_kierunku) {
		// lisc
		if (y[0] == 0 && y[1] == 0) {
			szukam_kierunku = false;
			dystans--;
			return -1;
		}
		// rozgalezienie z dobrej strony
		if (y[0] == 1 && y[1] + (pop_kraw == 1) > 1) {
			szukam_kierunku = false;
			return (pop_kraw = 0);
		}
		if (y[0] + (pop_kraw == 0) > 1 && y[1] == 1) {
			szukam_kierunku = false;
			return (pop_kraw = 1);
		}
		// rozgalezienie ze zlej strony
		if (y[0] == 0 && pop_kraw == 0 && y[1] > 1) {
			szukam_kierunku = false;
			dystans--;
			return -1;
		}
		if (y[0] > 1 && y[1] == 0 && pop_kraw == 1) {
			szukam_kierunku = false;
			dystans--;
			return -1;
		}
		
		for (int i = 1; i <= y[1]; i++) sciezka = (sciezka << 1) | 1;
		for (int i = 1; i <= y[0]; i++) sciezka = (sciezka << 1);
		if (dystans == 3) {
			szukam_kierunku = false;
			if (czy_cofaj[sciezka]) return -1;
			
			if (y[0] == 1 && y[1] == 0) return (pop_kraw = 0);
			if (y[0] == 0 && y[1] == 1) return (pop_kraw = 1);
			y[0] += (pop_kraw == 0);
			y[1] += (pop_kraw == 1);
			if (y[0] < y[1]) return (pop_kraw = 0);
			if (y[0] > y[1]) return (pop_kraw = 1);
			return -5;
		}
		
		dystans++;
		if (y[0] && !y[1]) return (pop_kraw = 0);
		if (!y[0] && y[1]) return (pop_kraw = 1);
		return -5;
	}
	
	if (y[0] == 1 && y[1] == 0) return (pop_kraw = 0);
	if (y[0] == 0 && y[1] == 1) return (pop_kraw = 1);
	y[0] += (pop_kraw == 0);
	y[1] += (pop_kraw == 1);
	if (y[0] < y[1]) return (pop_kraw = 0);
	if (y[0] > y[1]) return (pop_kraw = 1);
	return -5;
}
