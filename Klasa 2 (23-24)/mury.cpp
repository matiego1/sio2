#include <iostream>
#include <map>
using namespace std;

const int INF = 2 * 1000 * 1000 * 1000;
map<int, int> poz;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, h;
	cin >> n >> h;
	
	for (int i = 1; i <= n; i += 2) {
		int a;
		//od poludnia
		cin >> a;
		poz[1] = poz[1] + 1;
		poz[a + 1] = poz[a + 1] - 1;
		//od polnocy
		cin >> a;
		poz[h - a + 1] = poz[h - a + 1] + 1;
	}
	
	int suma = 0;
	int mini = INF;
	for (int i = 1; i <= h; i++) {
		suma += poz[i];
		mini = min(mini, suma);
	}
	
	int wynik = 0;
	suma = 0;
	for (int i = 0; i <= h; i++) {
		suma += poz[i];
		if (suma == mini) wynik++;
	}
	
	cout << mini << " " << wynik;

	return 0;
}

