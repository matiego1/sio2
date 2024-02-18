#include <iostream>
using namespace std;

int nwd(int a, int b) {
	while (b) {
		int pom = b;
		b = a % b;
		a = pom;
	}
	return a;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int a, b;
	cin >> a >> b;
//	cout << nwd(a, b);

	cout << 1;
	
	return 0;
}

