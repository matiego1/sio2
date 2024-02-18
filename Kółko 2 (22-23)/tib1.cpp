#include <iostream>
#include <algorithm>
using namespace std;

struct Sakwa {
	int x;
	int y;
	int masa;
	static Sakwa nowa(int x, int y, int masa) {
		Sakwa s;
		s.x = x;
		s.y = y;
		s.masa = masa;
		return s;
	}
};

const int R = (1 << 17);
int tree[2 * R];
const int MAX = 100 * 1000;
Sakwa sakwy[MAX];

int czytaj(int a, int b) {
	a += R;
	b += R;
	int wynik = max(tree[a], tree[b]);
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			wynik = max(wynik, tree[a + 1]);
		}
		if (b % 2 == 1) {
			wynik = max(wynik, tree[b - 1]);
		}
		a /= 2;
		b /= 2;
	}
	return wynik;
}

void ustaw(int index, int wart) {
	index += R;
	tree[index] = wart;
	while (index > 1) {
		index /= 2;
		tree[index] = max(tree[2 * index], tree[2 * index + 1]);
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;
	
	for (int i = 0; i < k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		sakwy[i] = Sakwa::nowa(a, b, c);
	}
	
	sort(sakwy, sakwy + k, [](Sakwa a, Sakwa b) {
		return a.y <= b.y;
	});
	
	int akt = 1, pop = sakwy[0].y;
	for (int i = 0; i < k; i++) {
		if (sakwy[i].y != pop) {
			akt++;
			pop = sakwy[i].y;
		}
		sakwy[i].y = akt;
	}

	sort(sakwy, sakwy + k, [](Sakwa a, Sakwa b) {
		if (a.x == b.x) return (a.y <= b.y);
		return (a.x < b.x);
	});
	
	for (int i = 0; i < k; i++) {
		ustaw(sakwy[i].y, czytaj(1, sakwy[i].y) + sakwy[i].masa);
	}
	
	cout << czytaj(1, akt);
	
	return 0;
}