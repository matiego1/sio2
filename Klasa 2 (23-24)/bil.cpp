#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
const int ALF = 26 + 26 + 10;
string s1, s2;
int ps[MAX + 5];
vector<int> indeksy[ALF];

int kod(char c) {
	//0-25 = a-z
	//26-51 = A-Z
	//52-61 = 0-9
	if ('a' <= c && c <= 'z') {
		return c - 'a';
	}
	if ('A' <= c && c <= 'Z') {
		return c - 'A' + 26;
	}
	return c - '0' + 26 + 26;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> s1 >> s2;
	int n = (int) s1.length(), m = (int) s2.length();
	s1 = "$" + s1;
	s2 = "$" + s2;
	
	ps[0] = -1;
	ps[1] = 0;
	for (int i = 2; i <= n; i++) {
		int wyn = ps[i - 1];
		while (wyn >= 0 && s1[i] != s1[wyn + 1]) {
			wyn = ps[wyn];
		}
		ps[i] = wyn + 1;
	}
	
	for (int i = 1; i <= n; i++) {
		indeksy[kod(s1[i])].push_back(i);
	}

	bool pocz = true;
	int wynik = 0, poz = 0;
	for (int i = 1; i <= m; i++) {
		auto p = upper_bound(indeksy[kod(s2[i])].begin(), indeksy[kod(s2[i])].end(), poz);
		if (p == indeksy[kod(s2[i])].end()) {
			if (pocz) {
				cout << "INF";
				return 0;
			}
			pocz = true;
			
			if (poz >= n - ps[n] + 1) {
				poz -= n - ps[n];
			} else {
				poz = 0;
			}
			
			wynik++;
			i--;
		} else {
			pocz = false;
			poz = *p;
		}
	}
	
	cout << wynik;

	return 0;
}
