#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Kraw {
	int x1, y1;
	int x2, y2;
	int w;
};

const int MAX = 1000;
int kra[2 * MAX * MAX];
Kraw kraw[2 * MAX * MAX];
bool poziome[MAX + 1][MAX + 1];
bool pionowe[MAX + 1][MAX + 1];

int pole(int x, int y) {
	return (y - 1) * MAX + x;
}

int findd(int x) {
	if (kra[x] == x) return x;
	return (kra[x] = findd(kra[x]));
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[a] = b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	int rozmiar = 0, chromowe = 0, tytanowe = 0;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x < m; x++) {
			char c;
			cin >> c;
			kraw[++rozmiar] = {x, y, x + 1, y, (c == 'T' ? 1 : 2)};
			if (c == 'T') tytanowe++;
			else chromowe++;
		}
	}
	
	for (int y = 1; y < n; y++) {
		for (int x = 1; x <= m; x++) {
			char c;
			cin >> c;
			kraw[++rozmiar] = {x, y, x, y + 1, (c == 'T' ? 1 : 2)};
			if (c == 'T') tytanowe++;
			else chromowe++;
		}
	}
	
	sort(kraw + 1, kraw + 1 + rozmiar, [](Kraw& k1, Kraw& k2) { return k1.w < k2.w; });
	
	for (int i = 1; i <= MAX * MAX; i++) kra[i] = i;
	
	int wyburzC = 0, wyburzT = 0;
	for (int i = 1; i <= rozmiar; i++) {
		Kraw& k = kraw[i];
		if (findd(pole(k.x1, k.y1)) == findd(pole(k.x2, k.y2))) continue;
		
		if (k.x1 == k.x2) {
			poziome[k.x1][k.y1] = true;
		} else {
			pionowe[k.x1][k.y1] = true;
		}
		
		unionn(pole(k.x1, k.y1), pole(k.x2, k.y2));
		if (k.w == 1) wyburzT++;
		else wyburzC++;
	}
	
	cout << (chromowe + tytanowe - wyburzT - wyburzC) << " " << (chromowe - wyburzC) << "\n";
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x < m; x++) {
			cout << (pionowe[x][y] ? '.' : 'Z');
		}
		cout << "\n";
	}
	
	for (int y = 1; y < n; y++) {
		for (int x = 1; x <= m; x++) {
			cout << (poziome[x][y] ? '.' : 'Z');
		}
		cout << "\n";
	}

	return 0;
}

