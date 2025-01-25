#include "owklib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 8000;
const int K = 12;
int kra[MAX];
vector<bool> wynik;

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

void mainA(int n, vector<para> edges) {
	for (int i = 0; i < n; i++) kra[i] = i;
	
	for (para& p : edges) {
		unionn(p.first, p.second);
	}
	
	for (int i = 0; i < n; i++) {
		for (int bit = K; bit >= 0; bit--) {
			send(kra[i] & (1 << bit));
		}
	}
}

void mainK(int n, vector<para> edges) {
	for (int i = 0; i < n; i++) {
		for (int bit = K; bit >= 0; bit--) {
			kra[i] = (kra[i] << 1) | receive();
		}
	}
	
	for (para& p : edges) {
		unionn(p.first, p.second);
	}
	
	wynik.resize(n);
	for (int i = 0; i < n; i++) {
		wynik[i] = (findd(i) == findd(0));
	}
	answer(wynik);
}
