#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Punkt {
	int x, y, indeks;
};

const int MAX = 200 * 1000;
Punkt wej[MAX + 1];
int grupyX[MAX + 10];
int grupyY[MAX + 10];
int kra[MAX + 1];

int findd(int x) {
	if (kra[x] == x) return x;
	return (kra[x] = findd(kra[x]));
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[a] = b;
}

int main() {
	int n, t;
	scanf("%d %d", &n, &t);
	
	const int MLD = 1000 * 1000 * 1000;
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		wej[i] = {x + MLD, y + MLD, i};
	}

	sort(wej + 1, wej + 1 + n, [](Punkt& p1, Punkt& p2) { return p1.x < p2.x; });
	int akt_x = 1;
	for (int i = 1; i < n; i++) {
		int akt = akt_x;
		if (wej[i].x < wej[i + 1].x) akt_x++;
		wej[i].x = akt;
	}
	wej[n].x = akt_x;
	
	sort(wej + 1, wej + 1 + n, [](Punkt& p1, Punkt& p2) { return p1.y < p2.y; });
	int akt_y = 1;
	for (int i = 1; i < n; i++) {
		int akt = akt_y;
		if (wej[i].y < wej[i + 1].y) akt_y++;
		wej[i].y = akt;
	}
	wej[n].y = akt_y;
	
	for (int i = 1; i <= n; i++) {
		kra[wej[i].indeks] = wej[i].indeks;
	}
	for (int i = 1; i <= n; i++) {
		Punkt& p = wej[i];
		if (grupyX[p.x] > 0) {
			unionn(p.indeks, grupyX[p.x]);
		}
		if (grupyY[p.y] > 0) {
			unionn(p.indeks, grupyY[p.y]);
		}
		int grupa = findd(p.indeks);
		grupyX[p.x] = grupa;
		grupyY[p.y] = grupa;
	}
	
	while (t--) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (findd(a) == findd(b)) {
			printf("TAK\n");
		} else {
			printf("NIE\n");
		}
	}

	return 0;
}

