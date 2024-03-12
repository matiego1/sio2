#include <iostream>
using namespace std;

const int MAX = 5000;
int DP[2][MAX + 1];
string wynik[2][MAX + 1];
char a[MAX];
char b[MAX];

void print_int(int x) {
	if (x == 0) return;
	print_int(x / 10);
	putchar((x % 10) + '0');
}

int main() {
	int znak, indeks = 0;
	while ('a' <= (znak = getchar()) && znak <= 'z') {
		a[indeks++] = znak;
	}
	int a_length = indeks;

	indeks = 0;
	while ('a' <= (znak = getchar()) && znak <= 'z') {
		b[indeks++] = znak;
	}
	int b_length = indeks;;

	for (int i = 0; i <= b_length; i++) {
		wynik[0][i] = "";
	}
	wynik[1][0] = "";

	for (int i = 1; i <= a_length; i++) {
		for (int j = 1; j <= b_length; j++) {
			if (a[i - 1] == b[j - 1]) {
				DP[i % 2][j] = DP[(i - 1) % 2][j - 1] + 1;
				wynik[i % 2][j] = wynik[(i - 1) % 2][j - 1] + a[i - 1];
			} else {
				if (DP[(i - 1) % 2][j] >= DP[i % 2][j - 1]) {
					DP[i % 2][j] = DP[(i - 1) % 2][j];
					wynik[i % 2][j] = wynik[(i - 1) % 2][j];
				} else {
					DP[i % 2][j] = DP[i % 2][j - 1];
					wynik[i % 2][j] = wynik[i % 2][j - 1];
				}
			}
		}
	}

	if (DP[a_length % 2][b_length] == 0) {
		putchar('0');
		return 0;
	}

	print_int(DP[a_length % 2][b_length]);
	putchar('\n');
	for (int i = 0; i < wynik[a_length % 2][b_length].length(); i++) {
		putchar(wynik[a_length % 2][b_length][i]);
	}

	return 0;
}
