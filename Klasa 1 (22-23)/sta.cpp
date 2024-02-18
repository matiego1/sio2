#include <iostream>
using namespace std;

string wej;

//sprawdza czy s³owo o pocz¹tku 'pocz' i koñcu 'kon' (w³¹cznie) jest palindromem
bool czy_pal(int pocz, int kon) {
	for (int i = 0; i <= (kon - pocz + 1) / 2; i++) {
		char a = wej[pocz + i];
		char b = wej[kon - i];
		if (a < 'a') a = a - 'A' + 'a';
		if (b < 'a') b = b - 'A' + 'a';
		if (a != b) return false;
	}
	return true;
}

//sprawdza czy znak jest liter¹
bool czy_litera(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

//zlicza ci¹gi znaków, dla których funkcja 'znak' (dla ka¿dego znaku w ci¹gu) uzwróci 'true'
int zlicz(bool (*znak)(char)) {
	int wynik = 0;
	bool rozpoczety = false;
	for (char c : wej) {
		if (znak(c)) {
			if (!rozpoczety) {
				wynik++;
				rozpoczety = true;
			}
		} else {
			rozpoczety = false;
		}
	}
	return wynik;
}

//zwraca wynik dla danego typu
int rozwiaz(int typ) {
	int wynik = 0;
	switch (typ) {
		case 1: {
			for (char c : wej) {
				if (c == ' ') wynik++;
			}
			break;
		}
		case 2: {
			wynik = zlicz([](char c) {
				return ('0' <= c && c <= '9');
			});
			break;
		}
		case 3: {
			wynik = zlicz(&czy_litera);
			break;
		}
		case 4: {
			bool dobre = false;
			for (char c : wej) {
				if (c == '.' && dobre) {
					wynik++;
					dobre = false;
				} else if (czy_litera(c)) {
					dobre = true;
				}
			}
			break;
		}
		case 5: {
			int poczatek = 0;
			bool rozpoczety = false;
			for (int i = 0; i < wej.length(); i++) {
				if (czy_litera(wej[i])) {
					if (!rozpoczety) {
						rozpoczety = true;
						poczatek = i;
					}
				} else if (rozpoczety) {
					rozpoczety = false;
					if (czy_pal(poczatek, i - 1)) wynik++;
				}
			}
			if (rozpoczety && czy_pal(poczatek, wej.length() - 1)) wynik++;
			break;
		}
	}
	return wynik;
}

int main() {
	
	int q;
	cin >> q;
	
	int zapyt[q];
	for (int i = 0; i < q; i++) cin >> zapyt[i];
	
	getline(cin, wej);
	getline(cin, wej);
	
	for (int i = 0; i < q; i++) {
		cout << rozwiaz(zapyt[i]) << " ";
	}
	
	return 0;
}
