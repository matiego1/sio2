#include <iostream>
using namespace std;

const double SKOK = 0.000001;
const int MAX = 6;
int a[MAX];

double f(double x) {
    return x*x*x*x*x*a[0] + x*x*x*x*a[1] + x*x*x*a[2] + x*x*a[3] + x*a[4] + a[5];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for (int i = 0; i < MAX; i++) {
		cin >> a[i];
	}
	
	bool znak = f(6) > 0;

	for (double i = 6; i >= -6; i -= SKOK) {
//		cout << i << " " <<  f(i) << endl;
		if (znak != (f(i) > 0)) {
			cout << i + SKOK;
			return 0;
		}
	}
	
	return 0;
}
