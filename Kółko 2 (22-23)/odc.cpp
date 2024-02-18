#include <iostream>
using namespace std;
typedef long long ll;

struct Punkt {
	ll x, y;
};
bool operator==(const Punkt& a, const Punkt& b) {
    return a.x == b.x && a.y == b.y;
}
Punkt wczytaj_punkt() {
	int x, y;
	cin >> x >> y;
	return {x, y};
}

int iloczyn(Punkt a, Punkt b, Punkt c) {
	ll wynik = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (wynik == 0) return 0;
	return (wynik > 0 ? 1 : -1);
}

bool odcinek(Punkt a, Punkt b, Punkt c) {
	return b.x <= max(a.x, c.x) && b.x >= min(a.x, c.x) && b.y <= max(a.y, c.y) && b.y >= min(a.y, c.y);
}

bool rozwiaz() {
	Punkt a1 = wczytaj_punkt(), a2 = wczytaj_punkt(), b1 = wczytaj_punkt(), b2 = wczytaj_punkt();
	
	if (a1 == b1 || a1 == b2 || a2 == b1 || a2 == b2) return true;
	
	int kierunek1 = iloczyn(a1, a2, b1);
	int kierunek2 = iloczyn(a1, a2, b2);
	int kierunek3 = iloczyn(b1, b2, a1);
	int kierunek4 = iloczyn(b1, b2, a2);
	
	if (kierunek1 == 0 && odcinek(a1, b1, a2)) return true;
	if (kierunek2 == 0 && odcinek(a1, b2, a2)) return true;
	if (kierunek3 == 0 && odcinek(b1, a1, b2)) return true;
	if (kierunek4 == 0 && odcinek(b1, a2, b2)) return true;
	
	return (kierunek1 != kierunek2 && kierunek3 != kierunek4);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	while (n--) {
		cout << (rozwiaz() ? "TAK\n" : "NIE\n");
	}

	return 0;
}