#include <iostream>
#include <stack>
using namespace std;

const int MAX = 1000 * 1000;
int pref[MAX + 1];
int wynik[MAX + 1];
stack<int> stos;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	
	string s;
	cin >> s;
	s = "$" + s;
	
	int indeks = 1;
	for (int i = 1; i < (int) s.length(); i++) {
		stos.push(i);
		pref[stos.size()] = pref[stos.size() - 1] + (s[i] == 'c' ? k : -1);
		
		if ((int) stos.size() - k - 1 < 0) continue;
		if (pref[stos.size()] - pref[stos.size() - k - 1] == 0) {
			for (int j = 1; j <= k + 1; j++) {
				wynik[indeks++] = stos.top();
				stos.pop();
			}
		}
	}
	
	for (int i = n; i >= 1; ) {
		for (int j = 1; j <= k + 1; j++) {
			cout << wynik[i--] << " ";
		}
		cout << "\n";
	}

	return 0;
}
