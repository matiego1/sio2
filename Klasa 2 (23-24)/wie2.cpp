#include <iostream>
using namespace std;
typedef long long ll;

struct Punkt {
	ll x, y;
};
Punkt wczytaj_punkt() {
	int x, y;
	scanf("%d %d", &x, &y);
	return {x, y};
}
bool operator==(const Punkt& a, const Punkt& b) {
    return a.x == b.x && a.y == b.y;
}

const int INF = 2 * 1000 * 1000 * 1000;
const int MAX = 1000 * 1000;
Punkt wej[MAX + 1];
int n;

int iloczyn(Punkt a, Punkt b, Punkt c) {
	ll wynik = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (wynik == 0) return 0;
	return (wynik > 0 ? 1 : -1);
}
bool na_odcinku(Punkt a, Punkt b, Punkt c) {
	return b.x <= max(a.x, c.x) && b.x >= min(a.x, c.x) && b.y <= max(a.y, c.y) && b.y >= min(a.y, c.y);
}
bool czy_sie_przecina(Punkt a1, Punkt a2, Punkt b1, Punkt b2) {
	if (a1 == b1 || a1 == b2 || a2 == b1 || a2 == b2) return true;
	
	int kierunek1 = iloczyn(a1, a2, b1);
	int kierunek2 = iloczyn(a1, a2, b2);
	int kierunek3 = iloczyn(b1, b2, a1);
	int kierunek4 = iloczyn(b1, b2, a2);
	
	if (kierunek1 == 0 && na_odcinku(a1, b1, a2)) return true;
	if (kierunek2 == 0 && na_odcinku(a1, b2, a2)) return true;
	if (kierunek3 == 0 && na_odcinku(b1, a1, b2)) return true;
	if (kierunek4 == 0 && na_odcinku(b1, a2, b2)) return true;
	
	return (kierunek1 != kierunek2 && kierunek3 != kierunek4);
}

int rozwiaz() {
	Punkt p1 = wczytaj_punkt();
	Punkt p2 = {INF + 62913911, p1.y + 1};
	
	int przeciecia = 0;
	for (int i = 0; i < n; i++) {
		if (iloczyn(wej[i], wej[i + 1], p1) == 0 && na_odcinku(wej[i], p1, wej[i + 1])) {
			return 0;
		}
		if (czy_sie_przecina(wej[i], wej[i + 1], p1, p2)) {
			przeciecia++;
		}
	}
	
	if (przeciecia % 2 == 0) {
		return 1;
	}
	return 2;
}

int main() {
	scanf("%d", &n);		
	
	for (int i = 0; i < n; i++) {
		wej[i] = wczytaj_punkt();
	}
	wej[n] = wej[0];
	
	int m;
	scanf("%d", &m);
	
	while (m--) {
		
		int x = rozwiaz();
		if (x == 0) {
			printf("KRAWEDZ\n");
		} else if (x == 1) {
			printf("NA ZEWNATRZ\n");
		} else {
			printf("WEWNATRZ\n");
		}
	}

	return 0;
}