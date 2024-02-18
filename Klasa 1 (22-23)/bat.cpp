#include <iostream>
#include <climits>
using namespace std;

const int MIN_INF = INT_MIN;
const int MAX = 1000 * 1000;
int wej[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> wej[i];
	}
	
	long long wynik = MIN_INF;
	long long akt = 0;
	for (int i = 0; i < n; i++) {
		akt += wej[i];
		wynik = max(wynik, akt);
		if (akt < 0) {
			akt = 0;
		}
	}
	
	cout << wynik;
	

	return 0;
}

