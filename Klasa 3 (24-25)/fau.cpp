#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Zapyt {
	char typ;
	int x, y;
};

const int MAX = 200 * 1000;
Zapyt zapyt[MAX + 1];
int kra[MAX + 1];
bool aktywne[MAX + 1];
vector<int> grupa[MAX + 1];
int wynik[MAX + 1];
vector<para> operacjeA;

int findd(int x) {
	if (kra[x] == x) return x;
	return (kra[x] = findd(kra[x]));
}

void unionn(int a, int b, int indeks) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	
	if (aktywne[a] && aktywne[b]) {
		kra[a] = b;
		return;
	}
	
	if (!aktywne[a] && !aktywne[b]) {
		if (grupa[a].size() > grupa[b].size()) swap(a, b);
		for (int x : grupa[a]) {
			grupa[b].push_back(x);
		}
		kra[a] = b;
		return;
	}
	
	if (aktywne[a]) swap(a, b);
	kra[a] = b;
	for (int x : grupa[a]) {
		wynik[x] = indeks;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		aktywne[i] = true;
		kra[i] = i;
	}
	
	operacjeA.push_back({-1, false});
	for (int i = 1; i <= q; i++) {
		cin >> zapyt[i].typ >> zapyt[i].x;
		if (zapyt[i].typ == 'A') {
			cin >> zapyt[i].y;
			operacjeA.push_back({i, true});
		} else if (zapyt[i].typ == 'R') {
			operacjeA[zapyt[i].x].second = false;
 			zapyt[i].y = zapyt[operacjeA[zapyt[i].x].first].y;
			zapyt[i].x = zapyt[operacjeA[zapyt[i].x].first].x;
		} else {
			aktywne[zapyt[i].x] = false;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (aktywne[i]) {
			wynik[i] = q;
		} else {
			grupa[i].push_back(i);
		}
	}
	
	for (para p : operacjeA) {
		if (!p.second) continue;
		unionn(zapyt[p.first].x, zapyt[p.first].y, q);
	}
	
	for (int i = q; i >= 1; i--) {
		if (zapyt[i].typ == 'A') continue;
		if (zapyt[i].typ == 'R') {
			unionn(zapyt[i].x, zapyt[i].y, i - 1);
		} else {
			int x = findd(zapyt[i].x);
			if (aktywne[x]) continue;
			aktywne[x] = true;
			for (int y : grupa[x]) {
				wynik[y] = i - 1;
			}
			grupa[x].clear();
		}
	}
	
	for (int i = 1; i <= n; i++) {
		cout << wynik[i] << "\n";
	}

	return 0;
}


