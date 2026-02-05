#include <bits/stdc++.h>
#include "caplib.h"
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 5000;
vector<int> graf[MAX + 1];
int liscie[MAX + 1];
int gleb[MAX + 1];
int maks_gleb[MAX + 1];
int ojciec[MAX + 1];
int wylaczone[MAX + 1];
vector<int> sciezka;

void dfs(int v, int p) {
	ojciec[v] = p;
	liscie[v] = v;
	
	for (int u : graf[v]) {
		if (u == p) continue;
		
		gleb[u] = gleb[v] + 1;
		dfs(u, v);
		if (gleb[liscie[u]] > gleb[liscie[v]]) {
			liscie[v] = liscie[u];
		}
	}
}

void dfs_gleb(int v, int p) {
	maks_gleb[v] = gleb[v];
	
	for (int u : graf[v]) {
		if (u == p) continue;
		
		dfs_gleb(u, v);
		maks_gleb[v] = max(maks_gleb[v], maks_gleb[u]);
	}
}

void dfs2(int v, int p) {
	int ile = 0;
	for (int u : graf[v]) {
		if (u == p) continue;
		if (wylaczone[u]) continue;
		ile++;
	}
	
	sciezka.push_back(v);
	
	for (int u : graf[v]) {
		if (u == p) continue;
		if (wylaczone[u]) continue;
		if (ile >= 2) {
			if (zapytaj(u)) {
				dfs2(u, v);
				return;
			}
		} else {
			dfs2(u, v);
		}
	}
}

int znajdz_capka(int n, vector<para> galezie) {
	sciezka.clear();
    for (int i = 1; i <= n; i++) {
		graf[i].clear();
		wylaczone[i] = false;
	}
	
    for (para& p : galezie) {
    	graf[p.first].push_back(p.second);
    	graf[p.second].push_back(p.first);
	}
	
	dfs(1, 1);
	
	for (int i = 1; i <= 70; i++) {
		if (zapytaj(liscie[1])) return liscie[1];
	}
	
	dfs_gleb(1, 1);
	
	for (int i = 1; i <= n; i++) {
		if (maks_gleb[i] - gleb[i] + 1 <= 70) {
			wylaczone[i] = true;
		}
	}
	if (wylaczone[1]) return 1;
	
	dfs2(1, 1);
	
	int pocz = 0, kon = (int) sciezka.size() - 1;
	while (pocz != kon) {
		int srodek = (pocz + kon + 1) / 2;
		if (zapytaj(sciezka[srodek])) {
			pocz = srodek;
		} else {
			kon = srodek - 1;
			if (pocz > 0) pocz--;
			if (kon > 0) kon--;
		}
	}
	
	return sciezka[pocz];
}
