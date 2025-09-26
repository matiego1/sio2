#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000 + 10;
int tab[MAX];
int poprzedni[MAX];
int nastepny[MAX];
int pozycja[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	int rozmiar = 0;
	int pocz = 0;
	
	for (int i = 1; i <= n; i++) {
		char typ;
		cin >> typ;
		
		if (typ == '>') {
			int x;
			cin >> x;
			
			rozmiar++;
			pozycja[i] = rozmiar;
			tab[rozmiar] = x;
			
			nastepny[rozmiar] = pocz;
			poprzedni[pocz] = rozmiar;
			
			pocz = rozmiar;
		} else if (typ == '+') {
			int x, y;
			cin >> x >> y;
			
			rozmiar++;
			pozycja[i] = rozmiar;
			tab[rozmiar] = x;
			
			int lewy = pozycja[y];
			int srodek = rozmiar;
			int prawy = nastepny[lewy];
			
			nastepny[lewy] = srodek;
			poprzedni[srodek] = lewy;
			
			nastepny[srodek] = prawy;
			poprzedni[prawy] = srodek;
		} else if (typ == '<') {
			pocz = nastepny[pocz];
		} else if (typ == '-') {
			int y;
			cin >> y;
			
			int element = pozycja[y];
			if (element == pocz) {
				pocz = nastepny[element];
			} else {
				int lewy = poprzedni[element];
				int prawy = nastepny[element];
				
				nastepny[lewy] = prawy;
				poprzedni[prawy] = lewy;
			}
		}
	}
	
	while (pocz) {
		cout << tab[pocz] << " ";
		pocz = nastepny[pocz];
	}

	return 0;
}

