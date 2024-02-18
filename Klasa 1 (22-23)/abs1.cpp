#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int maks = -2000000000, mini = 2000000000;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		maks = max(maks, a);
		mini = min(mini, a);
	}
	cout << maks - mini;
	return 0;
}
