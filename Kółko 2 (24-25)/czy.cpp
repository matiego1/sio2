#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000;
bool sito[MAX + 1];
vector<int> pierwsze;

void wygeneruj_pierwsze() {
	for (int i = 2; i <= MAX; i++) {
		sito[i] = true;
	}
	for (int i = 2; i * i <= MAX; i++) {
		if (sito[i]) {
			for (int j = i * i; j <= MAX; j += i) {
				sito[j] = false;
			}
		}
	}
	for (int i = 2; i <= MAX; i++) {
		if (sito[i]) {
			pierwsze.push_back(i);
		}
	}
}

void rozwiaz() {
	int x;
	cin >> x;
	
	for (int p : pierwsze) {
		if (p * p > x) break;
		while (x % p == 0) {
			cout << p << " ";
			x /= p;
		}
	}
	
	if (x > 1) {
		cout << x << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	wygeneruj_pierwsze();
	
	int t;
	cin >> t;
	
	while (t--) {
		rozwiaz();
	}

	return 0;
}