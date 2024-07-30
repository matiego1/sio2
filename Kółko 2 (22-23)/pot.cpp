#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Zapyt {
	int l, r, indeks;
};

const int K = 316;
const int MAX = 100 * 1000;
const int MAX_Ai = 1000 * 1000;
int wej[MAX + 1];
Zapyt zapytania[MAX + 1];
ll odp[MAX + 1];
ll zlicz[MAX_Ai + 1];
ll akt = 0;

void dodaj(int indeks) {
	ll wart = wej[indeks];
	akt -= zlicz[wart] * zlicz[wart] * wart;
	zlicz[wart]++;
	akt += zlicz[wart] * zlicz[wart] * wart;
}

void usun(int indeks) {
	ll wart = wej[indeks];
	akt -= zlicz[wart] * zlicz[wart] * wart;
	zlicz[wart]--;
	akt += zlicz[wart] * zlicz[wart] * wart;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, t;
	cin >> n >> t;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	for (int i = 1; i <= t; i++) {
		int a, b;
		cin >> a >> b;
		zapytania[i] = {a, b, i};		
	}
	
	sort(zapytania + 1, zapytania + 1 + t, [](Zapyt& z1, Zapyt& z2) { return make_pair(z1.l / K, z1.r) < make_pair(z2.l / K, z2.r); });
	
	int l = 0, r = -1;
	for (int i = 1; i <= t; i++) {
		Zapyt& z = zapytania[i];
		
		while (l > z.l) {
			l--;
			dodaj(l);
		}
		while (l < z.l) {
			usun(l);
			l++;
		}
		
		while (r < z.r) {
			r++;
			dodaj(r);
		}
		while (r > z.r) {
			usun(r);
			r--;
		}
		
		odp[z.indeks] = akt;
	}
	
	for (int i = 1; i <= t; i++) {
		cout << odp[i] << "\n";
	}

	return 0;
}



