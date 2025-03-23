#include <iostream>
using namespace std;

const int MAX = 8 * 1000 * 1000 * 2 + 5;
int ps[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	string wzorzec, tekst;
	cin >> wzorzec >> tekst;
	
	string s = "$" + wzorzec + "$" + tekst;
	
	ps[0] = -1;
	ps[1] = 0;
	for (int i = 2; i < s.length(); i++) {
		int wyn = ps[i - 1];
		while (wyn >= 0 && s[i] != s[wyn + 1]) {
			wyn = ps[wyn];
		}
		ps[i] = wyn + 1;
	}
	
	for (int i = n + 2; i < s.length(); i++) {
		if (ps[i] == n) {
			cout << i - 2 * n << "\n";
		}
	}
	
	return 0;
}