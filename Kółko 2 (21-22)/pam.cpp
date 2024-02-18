#include <iostream>
#define ll long long
using namespace std;

const int MAX = 1000 * 1000;
int wej[MAX];

ll minimum(int n) {
	ll wynik = wej[0], akt = 0;
	for (int i = 0; i < n; i++) {
		akt += wej[i];
		wynik = min(wynik, akt);
		if (akt > 0) {
			akt = 0;	
		}
		
	}
	return wynik; 
}

ll maksimum(int n) {
	ll wynik = wej[0], akt = 0;
	for (int i = 0; i < n; i++) {
		akt += wej[i];
		wynik = max(wynik, akt);
		if (akt < 0) {
			akt = 0;	
		}
		
	}
	return wynik; 
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	ll suma = 0, maks = -(1 << 30);
	bool ujemne = true;
	for (int i = 0; i < n; i++) {
		cin >> wej[i];
		suma += wej[i];
		maks = max(maks, (long long) wej[i]);
		if (wej[i] >= 0) {
			ujemne = false;
		}
	}
	
	if (ujemne) {
		cout << maks;
		return 0;
	}
	
	cout << max(suma - minimum(n), maksimum(n));
	
	return 0;
}