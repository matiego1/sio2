#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Punkt {
	ll x, y;
};
Punkt make_punkt(int x, int y) {
	return {x, y};
}

const int MAX = 200 * 1000;
Punkt wej[MAX + 1];

int iloczyn(Punkt a, Punkt b, Punkt c) {
	ll wynik = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (wynik == 0) return 0;
	return (wynik > 0 ? 1 : -1);
}

ll odleg_kw(Punkt a, Punkt b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool porownaj_punkty(Punkt& a, Punkt& b) {
	int kierunek = iloczyn(wej[1], b, a);
	
	if (kierunek == 0) {
		return odleg_kw(wej[1], a) < odleg_kw(wej[1], b);
	}
	return (kierunek == 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		wej[i] = make_punkt(a, b);
	}
	
	int mini_pkt = 1;
	for (int i = 2; i <= n; i++) {
		if (wej[i].x < wej[mini_pkt].x) {
			mini_pkt = i;
		} else if (wej[i].x == wej[mini_pkt].x && wej[i].y < wej[mini_pkt].y) {
			mini_pkt = i;
		}
	}
	swap(wej[1], wej[mini_pkt]);
	
	sort(wej + 2, wej + n + 1, porownaj_punkty);
	
	for (int i = 1; i <= n; i++) {
		cout << wej[i].x << " " << wej[i].y << "\n";
	}

	return 0;
}

