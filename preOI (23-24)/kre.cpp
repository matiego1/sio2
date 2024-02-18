#include <iostream>
#include <vector>
#include "krelib.hpp"
using namespace std;
typedef pair<int, int> para;

const int MAX = 5000;
vector<para> wynik;
int n;
bool odwie[MAX];
int numery[MAX];

int znajdz(int v, int numer) {
	int wynik = -1;
	for (int i = 1; i <= n; i++) {
		if (i == v) continue;
		if (odwie[i]) continue;
		if (numery[i] != numer) continue;
		if (wynik == -1 || query(v, i, wynik)) wynik = i;
	}
	return wynik;
}

void rekur(int v, int& numer) {
	odwie[v] = true;
	int oryginalny = numer;
	int syn;
	while ((syn = znajdz(v, oryginalny)) != -1) {
		wynik.push_back({v, syn});	
		
		odwie[syn] = true;
		numer++;
		
		for (int i = 1; i <= n; i++) {
			if (odwie[i]) continue;
			if (numery[i] != oryginalny) continue;
			if (query(v, syn, i)) numery[i] = numer;
		}
		
		rekur(syn, numer);
	}
}

int main() {
	int k, l;
	start(k, l);
	n = (1 << (k + 1)) - 1;
	
	int numer = 0;
	rekur(1, numer);

	answer(wynik);

	return 0;
}
