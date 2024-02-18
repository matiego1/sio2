#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

para wczytaj_punkt() {
	ll a, b;
	scanf("%lld %lld", &a, &b);
	return {a, b};
}

int iloczyn(para& a, para& b, para& c) {
	ll wynik = (b.second - a.second) * (c.first - b.first) - (b.first - a.first) * (c.second - b.second);
	if (wynik == 0) return 0;
	return (wynik > 0 ? 1 : -1);
}

bool odcinek(para& a, para& b, para& c) {
	return b.second <= max(a.second, c.second) && b.second >= min(a.second, c.second);
}

bool rozwiaz() {
	para a1 = wczytaj_punkt(), a2 = wczytaj_punkt(), b1 = wczytaj_punkt(), b2 = wczytaj_punkt();
	
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
	int n;
	scanf("%d", &n);
	
	while (n--) {
		if (rozwiaz()) {
			printf("TAK\n");
		} else {
			printf("NIE\n");
		}
	}

	return 0;
}