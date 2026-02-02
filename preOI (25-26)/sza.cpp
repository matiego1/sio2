#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_N = 200 * 1000;
const int MAX_M = 400 * 1000;
const int MOD = 1000 * 1000 * 1000 + 7;

struct Kraw {
	int a, b;
	ll w;
};
bool operator<(Kraw& k1, Kraw& k2) {
	return k1.w < k2.w;
}
Kraw kraw[MAX_M + 1];
int kra[MAX_N + 1];

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

bool czy_petelka0(Kraw& k) {
	return k.a == k.b && k.w == 0;
}

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), m = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
	}
	
	for (int i = 1; i <= m; i++) {
		kraw[i].a = wczytaj();
		kraw[i].b = wczytaj();
		kraw[i].w = wczytaj();
	}
	
	sort(kraw + 1, kraw + 1 + m);
	
	ll wynik = 1;
	for (int i = 1; i <= m; i++) {
		if (czy_petelka0(kraw[i])) {
			wynik = (wynik * 2) % MOD;
			continue;
		}
		
		if (i < m && kraw[i].w == kraw[i + 1].w && !czy_petelka0(kraw[i + 1])) {
			
			int a1 = findd(kraw[i].a), b1 = findd(kraw[i].b);
			if (a1 > b1) swap(a1, b1);
			int a2 = findd(kraw[i + 1].a), b2 = findd(kraw[i + 1].b);
			if (a2 > b2) swap(a2, b2);
			
			if (a1 != b1 && a1 == a2 && b1 == b2) {
				unionn(a1, b1);
				if (kraw[i].w == 0) {
					wynik = (wynik * 3) % MOD;
				} else {
					wynik = (wynik * 2) % MOD;
				}
			} else {
				unionn(a1, b1);
				unionn(a2, b2);
			}
			
			i++;
		} else {
			unionn(kraw[i].a, kraw[i].b);
		}
	}
	printf("%lld", wynik);

	return 0;
}

