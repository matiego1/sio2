#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
int wej[MAX + 1];
int grupa[MAX + 1];
int n;

const bool DEBUG = false;

bool sprawdz(int drugi) {
	// 1) Ciag monotoniczny
	for (int i = 1; i <= n; i++) grupa[i] = 0;
	
	int r = wej[2] - wej[1];
	int akt = wej[2] + r;
	int przod = 2;
	for (int i = 3; i <= n; i++) {
		if (wej[i] == akt) {
			akt += r;
			przod++;
		} else break;
	}
	
	r = wej[n - 1] - wej[n];
	akt = wej[n - 1] + r;
	for (int i = n - 2; i >= przod - 1; i--) {
		if (wej[i] == akt) {
			akt += r;
		} else break;
		if (i == przod) {
			for (int i = 1; i <= n; i++) grupa[i] = 2;
			return true;
		}
	}
	
	// 2) Ciag bitoniczny	
	for (int i = 1; i <= n; i++) grupa[i] = 0;
	
	int ostatni = -1;
	r = wej[drugi] - wej[1];
	akt = wej[1] + r;
	for (int i = 2; i <= n; i++) {
		if (wej[i] == akt) {
			grupa[i] = 1;
			akt += r;
			ostatni = i;
		}
	}
	
	bool wziety_ostatni = false;
	r = INT_MIN;
	for (int i = 2; i <= n; i++) {
		if (grupa[i] != 0 && r == INT_MIN) continue;
		if (r == INT_MIN) {
			r = wej[i] - wej[1];
			akt = wej[i] + r;
			grupa[i] = 2;
			continue;
		}
		if (wej[i] == akt) {
			if (grupa[i] == 0) {
				wziety_ostatni = false;
				grupa[i] = 2;
				akt += r;
			} else if (ostatni == i) {
				grupa[i] = 2;
				akt += r;
				wziety_ostatni = true;
			}
		} else if (wziety_ostatni && wej[i] == wej[ostatni]) {
			wziety_ostatni = false;
			grupa[ostatni] = 1;
			grupa[i] = 2;
		}
	}
	
	bool ok = true;
	for (int i = 2; i <= n; i++) {
		if (grupa[i] == 0) {
			ok = false;
			break;
		}
	}
	if (ok) return true;
	
	for (int i = 1; i <= n; i++) {
		if (grupa[i] == 2) grupa[i] = 0;
	}
	grupa[ostatni] = 2;
	r = wej[ostatni] - wej[1];
	akt = wej[ostatni] + r;
	
 	for (int i = 2; i <= n; i++) {
		if (grupa[i] != 0) continue;
		if (wej[i] == akt) {
			grupa[i] = 2;
			akt += r;
		}
	}
	
	for (int i = 2; i <= n; i++) {
		if (grupa[i] == 0) return false;
	}
	return true;
}

void rozwiaz() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	sort(wej + 1, wej + 1 + n);
	
	bool wynik = sprawdz(2);
	if (!wynik) wynik = sprawdz(3);
	if (!wynik) {
		reverse(wej + 1, wej + 1 + n);
		wynik = sprawdz(2);
	}
	if (!wynik) wynik = sprawdz(3);
	
	if (wynik) {
		cout << "TAK\n";
		
		for (int i = n; i >= 2; i--) {
			if (grupa[i] == 1) cout << wej[i] << " ";			
		}
		cout << wej[1] << " ";
		for (int i = 2; i <= n; i++) {
			if (grupa[i] == 2) cout << wej[i] << " ";
		}
		
	} else {
		cout << "NIE";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	
	while (t--) {
		rozwiaz();
	}

	return 0;
}

