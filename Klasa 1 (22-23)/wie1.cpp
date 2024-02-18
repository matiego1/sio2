#include <iostream>
#include <algorithm>
using namespace std;
struct Miesz {
	int wys;
	int wynik;
	int pozycja;
	static Miesz nowy(int wys, int wynik, int pozycja) {
		Miesz miesz;
		miesz.wys = wys;
		miesz.wynik = wynik;
		miesz.pozycja = pozycja;
		return miesz;
	}
};

const int MAX = 500 * 1000;
int wej[MAX];
Miesz ludzie[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) {
		cin >> wej[i];
	}
	
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		ludzie[i] = Miesz::nowy(a, 0, i);
	}
	
	sort(ludzie, ludzie + m, [](Miesz m1, Miesz m2) {
		return (m1.wys < m2.wys);
	});
	
	int indeks = -1;
	for (int i = 0; i < m; i++) {
		while (indeks < n - 1 && ludzie[i].wys > wej[indeks + 1]) {
			indeks++;
		}
		ludzie[i].wynik = indeks + 1;
	}
	
	sort(ludzie, ludzie + m, [](Miesz m1, Miesz m2) {
		return (m1.pozycja < m2.pozycja);
	});
	
	for (int i = 0; i < m; i++) {
		cout << ludzie[i].wynik << " ";
	}

	return 0;
}

