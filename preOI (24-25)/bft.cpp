#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int MAX_Ai = 500 * 1000;
int dp[MAX + 1];
int kra[MAX_Ai + 1];
int rozmiar[MAX_Ai + 1];

int findd(int x) {
	if (kra[x] == x) return x;
	return (kra[x] = findd(kra[x]));
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	
	if (rozmiar[a] > rozmiar[b]) swap(a, b);
	kra[a] = b;
	rozmiar[b] += rozmiar[a];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	dp[1] = 1;	
	for (int i = 2; i <= n; i++) {
		dp[i] = max(dp[i - 1], dp[i - 2] + 1);
	}
	for (int i = 1; i <= MAX_Ai; i++) {
		kra[i] = i;
		rozmiar[i] = 0;
	}
	
	int wynik = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		
		if (rozmiar[findd(a)] > 0) {
			cout << wynik << " ";
			continue;
		}
		
		rozmiar[a] = 1;
		
		if (a - 1 >= 1) {
			int lewy = findd(a - 1);
			if (rozmiar[lewy] > 0) {
				wynik -= dp[rozmiar[lewy]];
				unionn(a, lewy);
			}
		}
		if (a + 1 <= MAX_Ai) {
			int prawy = findd(a + 1);
			if (rozmiar[prawy] > 0) {
				wynik -= dp[rozmiar[prawy]];
				unionn(a, prawy);
			}
		}
		
		wynik += dp[rozmiar[findd(a)]];
		
		cout << wynik << " ";
	}

	return 0;
}

