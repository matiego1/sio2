#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	int T[n];
	for (int i = 0; i < n; i++) cin >> T[i];
	
	int mini = T[n - 1] + 1;
	long long wynik = 0;
	for (int i = n - 1; i >= 0; i--) {
		mini = min(mini, T[i]);
		wynik += mini;
	}
	
	cout << wynik;
	
	return 0;
}