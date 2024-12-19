#include <iostream>
#include <algorithm>
using namespace std;

struct Krawedz {
	int v, u, waga;
	int indeks;
};
Krawedz make_krawedz(int v, int u, int waga, int indeks) {
	return {v, u, waga, indeks};
}
bool operator<(Krawedz& a, Krawedz& b) {
	return a.waga < b.waga;
}

const int MAX_N = 200 * 1000;
const int MAX_M = 300 * 1000;

Krawedz krawedzie[MAX_M + 1];
bool odpowiedzi[MAX_M + 1];

int kra[MAX_N + 1];
int findd(int x) {
    if (x == kra[x]) return x;
    kra[x] = findd(kra[x]);
    return kra[x];
}
void unionn(int a, int b) {
    a = findd(a);
    b = findd(b);
    kra[b] = a;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		kra[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		krawedzie[i] = make_krawedz(a, b, c, i);
	}
	
	sort(krawedzie + 1, krawedzie + m + 1);
	
	odpowiedzi[krawedzie[1].indeks] = true;
	int laczenie = 1;
	for (int i = 2; i <= m; i++) {
		if (krawedzie[i].waga != krawedzie[i - 1].waga) {
			while (laczenie < i) {
				if (odpowiedzi[krawedzie[laczenie].indeks]) {
					unionn(krawedzie[laczenie].v, krawedzie[laczenie].u);
				}
				laczenie++;
			}
		}
		
		if (findd(krawedzie[i].v) == findd(krawedzie[i].u)) continue;
		odpowiedzi[krawedzie[i].indeks] = true;
	}
	
	for (int i = 1; i <= m; i++) {
		cout << (odpowiedzi[i] ? "TAK\n" : "NIE\n");
	}

	return 0;
}