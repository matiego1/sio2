#include <iostream>
using namespace std;

const int MAX = 1000 * 1000;
int ps[MAX + 5];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int k;
	cin >> k >> k;
	string wej;
	cin >> wej;
	wej = "$" + wej;
	
	ps[0] = -1;
	ps[1] = 0;
	for (int i = 2; i < wej.length(); i++) {
		int wyn = ps[i - 1];
		while (wyn >= 0 && wej[i] != wej[wyn + 1]) {
			wyn = ps[wyn];
		}
		ps[i] = wyn + 1;
	}
	
	for (int i = 1; i < wej.length(); i++) {
		cout << (int) (i / (i - ps[i]) >= k);
	} 
	
	return 0;
}
