#include <iostream>
using namespace std;

const int ALF = 'z' - 'a' + 1;
int t1[ALF];
int t2[ALF];
int wynik[ALF];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string a, b;
	cin >> a >> b;
	
	for (int i = 0; i < a.length(); i++) {
		t1[a[i] - 'a']++;
	}
	for (int i = 0; i < b.length(); i++) {
		t2[b[i] - 'a']++;
	}
	
	int suma = 0;
	for (int i = 0; i < ALF; i++) {
		wynik[i] = min(t1[i], t2[i]);
		t1[i] = 0;
		t2[i] = 0;
		suma += wynik[i];
	}
	
	if (suma == 0) {
		cout << "BRAK";
		return 0;
	}
	
	cout << suma << "\n";
	for (int i = 0; i < a.length(); i++) {
		if (t1[a[i] - 'a'] < wynik[a[i] - 'a']) {
			t1[a[i] - 'a']++;
			cout << a[i];
		}
	}
	cout << "\n" << suma << "\n";
	for (int i = 0; i < b.length(); i++) {
		if (t2[b[i] - 'a'] < wynik[b[i] - 'a']) {
			t2[b[i] - 'a']++;
			cout << b[i];
		}
	}
	
	return 0;
}