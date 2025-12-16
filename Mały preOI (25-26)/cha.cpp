#include "chalib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Trojka {
	int kolor1, srodek, kolor0;
};

vector<int> sciezka;
vector<Trojka> trojki;
vector<para> wynik;

void zakoncz() {
	odpowiedz(wynik);
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n = daj_n();
	
	if (n == 1) zakoncz();
	
	bool kolor_sciezki = true;
	for (int i = 1; i <= n; i++) {
		if (sciezka.empty()) {
			sciezka.push_back(i);
			continue;
		}
		if (sciezka.size() == 1) {
			kolor_sciezki = zapytaj(sciezka.back(), i);
			sciezka.push_back(i);
			continue;
		}
		
		bool nowy_kolor = zapytaj(sciezka.back(), i);
		if (nowy_kolor == kolor_sciezki) {
			sciezka.push_back(i);
			continue;
		}
		
		int srodek = sciezka.back();
		sciezka.pop_back();
		int kolor1 = sciezka.back();
		sciezka.pop_back();
		int kolor0 = i;
		
		if (nowy_kolor) swap(kolor1, kolor0);
		
		trojki.push_back({kolor1, srodek, kolor0});
	}
	
	while (sciezka.size() >= 2) {
		int a = sciezka.back();
		sciezka.pop_back();
		int b = sciezka.back();
		sciezka.pop_back();
		
		wynik.push_back({a, b});
	}

	for (Trojka& t : trojki) {
		if (kolor_sciezki) {
			wynik.push_back({t.kolor1, t.srodek});
		} else {
			wynik.push_back({t.kolor0, t.srodek});
		}
	}
	
	zakoncz();

	return 0;
}

