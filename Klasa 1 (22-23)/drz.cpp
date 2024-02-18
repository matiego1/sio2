#include <iostream>
using namespace std;

const int MAX = 1000;
int pref[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	cin >> s;
	
	for (int i = 1; i <= s.length(); i++) {
		pref[i] = pref[i - 1];
		if (s[i - 1] == 'b') {
			pref[i]++;
		}
	}
	
	int q;
	cin >> q;
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << pref[b] - pref[a - 1] << "\n";
	}

	return 0;
}

