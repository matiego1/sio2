#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
multiset<int> zbior_A;
multiset<int> zbior_B;
char s1[MAX + 1];
char s2[MAX + 1];
int A[MAX + 1];
int B[MAX + 1];
int p_a[MAX + 1];
int p_b[MAX + 1];
int n;

int f(char c) {
	if (c == 'A') return 0;
	if (c == 'G') return 1;
	return 2;
}

ll policz(int x, int y) {
	int zlicz = 0, indeks = 0;
	for (int i = 1; i <= n; i++) {
		if (A[i] == x) zlicz++;
		if (A[i] == y) p_a[++indeks] = zlicz;
	}
	
	zlicz = 0;
	indeks = 0;
	for (int i = 1; i <= n; i++) {
		if (B[i] == x) zlicz++;
		if (B[i] == y) p_b[++indeks] = zlicz;
	}
	
	ll wynik = 0;
	for (int i = 1; i <= indeks; i++) {
		wynik += abs(p_a[i] - p_b[i]);
	}
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> s1[i];
		
		A[i] = (i + f(s1[i])) % 3;
		zbior_A.insert(A[i]);
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> s2[i];
		B[i] = (i + f(s2[i])) % 3;
		zbior_B.insert(B[i]);
	}
	
	if (zbior_A != zbior_B) {
		cout << "Nie";
		return 0;
	}
	
	cout << "Tak\n";
	
	cout << policz(0, 1) + policz(1, 2) + policz(2, 0);

	return 0;
}

