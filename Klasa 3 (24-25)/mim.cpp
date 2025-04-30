#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
 
const int MAX = 40;
int wej[MAX + 1];
vector<ll> sumy1;
vector<ll> sumy2;
 
void generuj(int pocz, int kon, vector<ll>& sumy) {
	int n = kon - pocz + 1;
	for (int maska = 0; maska < (1 << n); maska++) {
		ll suma = 0;
		for (int i = pocz; i <= kon; i++) {
			if (maska & (1 << (i - pocz))) {
				suma += wej[i];
			}
		}
		sumy.push_back(suma);
	}
}
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	int n, x;
	cin >> n >> x;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	generuj(1, n / 2, sumy1);
	generuj(n / 2 + 1, n, sumy2);
	
	sort(sumy2.begin(), sumy2.end());
	
	ll wynik = 0;
	for (ll suma : sumy1) {
		auto pocz = lower_bound(sumy2.begin(), sumy2.end(), x - suma);
		auto kon = upper_bound(sumy2.begin(), sumy2.end(), x - suma);
		wynik += kon - pocz;
	}
	cout << wynik;
 
	return 0;
}

