#include "wydlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int GORA = 5;
const int DOL = 4;
const int LEWO = 3;
const int PRAWO = 2;
bool wykorzystane[15];

const vector<para> pola = {
	{0, 1},
	{0, 2},
	{1, 0},
	{1, 1},
	{1, 2},
	{2, 0},
	{2, 1},
	{2, 2}
};

int wartosc(int x, int y, int wyr_x, int wyr_y) {
	int del_x = wyr_x - x, del_y = wyr_y - y;
	
	int wart_y = -1;
	if (del_y == -1) wart_y = 0;
	else if (del_y == 0) wart_y = 1;
	else if (del_y == 1) wart_y = 2;
	
	if (wart_y >= 0) {
		if (del_x == -1) return 6 + wart_y;
		if (del_x == 0) return 9 + wart_y;
		if (del_x == 1) return 12 + wart_y;
	}
	
	if (abs(del_x) > abs(del_y)) {
		if (wyr_x < x) return GORA;
		if (wyr_x > x) return DOL;
	} else {
		if (wyr_y < y) return LEWO;
		if (wyr_y > y) return PRAWO;
	}
	
	return 0;
}

void ustaw(int x, int y, int wyr_x, int wyr_y, int n, vector<vector<int>>& tab) {
	if (x < 0 || x > n - 1) return;
	if (y < 0 || y > n - 1) return;
	
	tab[x][y] = wartosc(x, y, wyr_x, wyr_y);
	wykorzystane[tab[x][y]] = true;
}

bool rozwiaz(int n, array<int, K> A, array<int, K> B, vector<vector<int>>& tab, int WYR_X, int WYR_Y) {
	for (int i = 6; i <= 14; i++) wykorzystane[i] = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tab[i][j] = 2;
		}
	}
	
	for (int x = WYR_X - 3; x <= n; x += 3) {
		for (int y = WYR_Y - 3; y <= n; y += 3) {
			for (int i = 0; i < K; i++) {
				ustaw(x + pola[i].first, y + pola[i].second, A[i], B[i], n, tab);
			}
			
			if (x < 0 || x > n - 1) continue;
			if (y < 0 || y > n - 1) continue;
			tab[x][y] = 1;
		}
	}
	
		
	int wolne = 15;
	for (int i = 6; i <= 14; i++) {
		if (wykorzystane[i]) continue;
		wolne = i;
		break;
	}
	
	for (int x = WYR_X - 3; x <= n; x += 3) {
		for (int y = WYR_Y - 3; y <= n; y += 3) {
			int x1 = x + pola[K].first;
			int y1 = y + pola[K].second;
			
			if (x1 < 0 || x1 > n - 1) continue;
			if (y1 < 0 || y1 > n - 1) continue;
			
			tab[x1][y1] = (wolne == 13 ? 2 : wolne);
		}
	}
	
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (tab[x][y] > wolne) tab[x][y]--;
		}
	}
	
	if (wykorzystane[14]) return false;
	if (wolne >= 14) return false;
	return true;
}

vector<vector<int>> Bitek(int n, array<int, K> A, array<int, K> B) {
	vector<vector<int>> tab = vector<vector<int>>(n, vector<int>(n, 2));
	
	for (int x = 0; x <= 2; x++) {
		for (int y = 0; y <= 2; y++) {
			if (rozwiaz(n, A, B, tab, x, y)) return tab;
		}
	}
	return tab;
}

int znajdz_wolne(int wyr_x, int wyr_y, array<int, 9>& A) {
	int x = (wyr_x + pola[K].first + 3) % 3;
	int y = (wyr_y + pola[K].second + 3) % 3;
	int wolne = A[3 * x + y];
	if (wolne == 2) wolne = 13;
	return wolne;
}

array<int, K> Bajtazar(array<int, 9> A) {
	array<int, K> tab = array<int, K>{0};
	
	int wyr_x = 0, wyr_y = 0;
	for (int i = 0; i < 9; i++) {
		if (A[i] == 1) {
			wyr_x = i / 3;
			wyr_y = i % 3;
			break;
		}
	}
	
	int wolne = znajdz_wolne(wyr_x, wyr_y, A);
	for (int i = 0; i < 9; i++) {
		if (A[i] >= wolne) A[i]++;
	}
	
	for (int i = 0; i < K; i++) {
		int x = (wyr_x + pola[i].first + 3) % 3;
		int y = (wyr_y + pola[i].second + 3) % 3;
		int wart = A[3 * x + y];
		
		if (wart <= 5) {
			tab[i] = wart - 2;
			continue;
		}
		
		if (wart == 6) x--, y--;
		else if (wart == 7) x--;
		else if (wart == 8) x--, y++;
		
		else if (wart == 9) y--;
		else if (wart == 10) {}
		else if (wart == 11) y++;
		
		else if (wart == 12) x++, y--;
		else if (wart == 13) x++;
		else if (wart == 14) x++, y++;
		
		if (x < 1) tab[i] = GORA;
		else if (x > 1) tab[i] = DOL;
		else if (y < 1) tab[i] = LEWO;
		else if (y > 1) tab[i] = PRAWO;
		else tab[i] = 6; // stoj
		tab[i] -= 2;
	}
	
	return tab;
}

