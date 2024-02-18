#include <iostream>
using namespace std;

const int MOD = 1000 * 1000 * 1000 + 7;
const int P = 1259689; //https://www.algorytm.edu.pl/images/prim100000.txt
const int MAX = 2 * 1000 * 1000;
long long potegi[MAX];

long long pos(char c) {
	return c - 'a' + 1;
}

int modUjemne(int a, int b) {
	return (a < 0 ? (b + a) % b : a % b);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	long long akt = 1;
	for (int i = 0; i < MAX; i++) {
		potegi[i] = akt;
		akt = (akt * P) % MOD;
	}
	
	string a, b;
	cin >> a >> b;
	int n = a.length(), m = b.length();
	
	if (n > m) {
		cout << 0;
		return 0;
	}
	if (n == m) {
		cout << (a == b);
		return 0;
	}
	
	int hashA = 0;
	for (int i = 0; i < n; i++) {
		hashA = (potegi[n - i - 1] * pos(a[i]) + hashA) % MOD;
	}
	
	long long pref[m + 1];
	pref[0] = 0;
	for (int i = 1; i <= m; i++) {
		pref[i] = (pref[i - 1] * P + pos(b[i - 1])) % MOD;
	}
	
	int wynik = 0;
	for (int i = 1; i <= m - n + 1; i++) {
		int L = i;
		int R = i + n - 1;
		if (modUjemne(pref[R] - ((pref[L - 1] * potegi[n]) % MOD), MOD) == hashA) wynik++;
	}
	cout << wynik;
	
	return 0;
}
