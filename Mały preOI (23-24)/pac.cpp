#include <iostream>
using namespace std;

const int INF = 1000 * 1000 * 1000;
const int MAX = 2 * 100 * 1000;
int n;
int wej[MAX + 1];

bool czy_parz(int x) {
	return abs(x) % 2 == 0;
}

int rozwiaz1() {
	int maks = -INF, akt = wej[1];
	for (int i = 2; i <= n; i++) {
		if (czy_parz(wej[i]) == czy_parz(wej[i - 1])) {
			maks = max(maks, akt);
			akt = wej[i];
		} else {
			akt += wej[i];
		}
	}
	maks = max(maks, akt);
	
	return maks;
}

int rozwiaz4() {
	int maks = -INF, akt = 0;
	for (int i = 1; i <= n; i++) {
		akt = max(akt + wej[i], 0);
		maks = max(maks, akt);
	}
	
	if (maks == 0) {
		for (int i = 1; i <= n; i++) {
			maks = max(maks, -wej[i]);
		}
		maks = -maks;
	}
	
	return maks;
}

int rozwiaz_przedzial(int a, int b) {
	int maks = -INF, akt = 0;
	bool same_ujemne = true;
	for (int i = a; i <= b; i++) {
		if (wej[i] >= 0) {
			same_ujemne = false;
		}
		akt = max(akt + wej[i], 0);
		maks = max(maks, akt);
	}
	
	if (same_ujemne) {
		maks = -INF;
		for (int i = a; i <= b; i++) {
			maks = max(maks, wej[i]);
		}
		maks = maks;
	}
	
	return maks;
}

int rozwiaz() {
	int maks = wej[1], pocz = 1;
	for (int kon = 2; kon <= n; kon++) {
		if (czy_parz(wej[kon]) == czy_parz(wej[kon - 1])) {
			maks = max(maks, rozwiaz_przedzial(pocz, kon - 1));
			pocz = kon;
		}
	}
	return max(maks, rozwiaz_przedzial(pocz, n));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		cin >> n;
		
		for (int i = 1; i <= n; i++) {
			cin >> wej[i];
		}

		cout << rozwiaz() << "\n";
	}

	return 0;
}
