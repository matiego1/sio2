#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long wa, b, m;
	cin >> wa >> b >> m;
        __int128 a = wa;
	
	long long wyn = 1;
	while (b > 0) {
		if (b & 1) {
			wyn = (wyn * a) % m;
		}
		a = (a * a) % m;
		b /= 2;
	}
	cout << wyn;
	
	return 0;
}