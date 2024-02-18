#include <iostream>
#include <vector>
#include <map>
#include "sejlib.h"
using namespace std;

const int MAX = 10 * 1000;

int n;
int odpowiedzi[MAX + 1];

map<int, int> zlicz;

int czy_klamie(int prawdomowny, int do_sprawdzenia) {
	int trzeci = -1;
	for (int i = 1; i <= n; i++) {
		if (i == prawdomowny) continue;
		if (i == do_sprawdzenia) continue;
		trzeci = i;
		break;
	}
	
	int a = wywiad(prawdomowny, trzeci);
	if (a == -1) return -1;
	
	int b = wywiad(do_sprawdzenia, trzeci);
	if (b == -1) return -1;
	
	return a != b;
}

int main() {
	n = init();
	
	for (int i = 2; i <= n; i++) {
		int x = wywiad(i, 1);
		if (x == -1) return 0;
		
		odpowiedzi[i] = x;
		zlicz[x] += 1;
	}
	
	int maks = 0, lider;
	for (pair<int, int> i : zlicz) {
		if (i.second > maks) {
			maks = i.second;
			lider = i.first;
		}
	}
	int liderzy = 0;
	for (pair<int, int> i : zlicz) {
		if (i.second == maks) {
			liderzy++;
		}
	}
	
	if (liderzy == 1) {
		vector<int> klamcy;
		
		for (int i = 2; i <= n; i++) {
			if (odpowiedzi[i] == lider) {
				int x = czy_klamie(i, 1);
				if (x == -1) return 0;
				if (x == 1) {
					klamcy.push_back(1);
				}
				break;
			}
		}
		
		for (int i = 2; i <= n; i++) {
			if (odpowiedzi[i] != lider) {
				klamcy.push_back(i);
			}
		}
		
		odpowiedz(klamcy);
		return 0;
	}

	int x = czy_klamie(1, 2);
	if (x == -1) return 0;
	
	vector<int> klamcy;
	if (x == 1) {
		for (int i = 2; i <= n; i++) {
			if (odpowiedzi[i] == odpowiedzi[2]) {
				klamcy.push_back(i);
			}
		}
	} else {
		for (int i = 2; i <= n; i++) {
			if (odpowiedzi[i] != odpowiedzi[2]) {
				klamcy.push_back(i);
			}
		}
	}
	odpowiedz(klamcy);
 	
	return 0;
}


