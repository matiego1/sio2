#include <iostream>
#include <vector>
#include "stu2lib.h"
using namespace std;

const int INF = 1000 * 1000 * 1000;
const int R = (1 << 18);

int n;
int tree[2 * R];

int query(int a, int b) { // minimum na przedziale
	if (a < 0 || b < 0) return INF;
	
	a += R;
	b += R;
	
	int wynik = min(tree[a], tree[b]);
	while (a / 2 != b / 2) {
		if (a % 2 == 0) {
			wynik = min(wynik, tree[a + 1]);
		}
		if (b % 2 == 1) {
			wynik = min(wynik, tree[b - 1]);
		}
		
		a /= 2;
		b /= 2;
	}
	
	return wynik;
}

void inicjuj(vector<int> arr) {
	n = arr.size();
	
	for (int i = 1; i < 2 * R; i++) {
		tree[i] = INF;
	}
	for (int i = 0; i < n; i++) {
		tree[R + i] = arr[i];
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
}

int odpowiedz(int a, int b) {
	a--;
	b--;
	
	return min(min(query(0, a - 1), query(b + 1, n)), n);
}

void zamien(int a, int b) {
	a += R - 1;
	b += R - 1;
	
	swap(tree[a], tree[b]);
	
	while (a > 1) {
		a /= 2;
		tree[a] = min(tree[2 * a], tree[2 * a + 1]);
	}
	while (b > 1) {
		b /= 2;
		tree[b] = min(tree[2 * b], tree[2 * b + 1]);
	}
}
