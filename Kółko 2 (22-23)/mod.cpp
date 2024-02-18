#include <iostream>
using namespace std;

long long silnia(int a, int p) {
	long long wynik = 1;
	
	for (long long i = 2; i <= a; i++) {
		wynik = (wynik * i) % p;
	}
	
	return wynik;
}

int pot(long long a, long long b, int p) {
	long long wyn = 1;
	while (b > 0) {
		if (b & 1) {
			wyn = (wyn * a) % p;
		}
		a = (a * a) % p;
		b /= 2;
	}
	return wyn;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, p;
	cin >> n >> m >> p;

	long long licznik = silnia(m + n, p);
	long long mianownik = (silnia(m, p) * silnia(n, p)) % p;
	
	cout << (licznik * pot(mianownik, p - 2, p)) % p;
	
	return 0;
}
