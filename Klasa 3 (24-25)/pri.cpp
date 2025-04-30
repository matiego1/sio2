#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;
 
const int MAX = 20;
ll wej[MAX + 1];
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	ll n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= k; i++) {
		cin >> wej[i];
	}
	
	ll wynik = 0;
	
	for (int maska = 1; maska < (1 << k); maska++) {
		int znak = (__builtin_popcount(maska) % 2 == 0 ? -1 : 1);
		
		ll ile = n;
		for (int i = 1; i <= k; i++) {
			if (maska & (1 << (i - 1))) {
				ile /= wej[i];
			}
		}
		
		wynik += ile * znak;
	}
	
	cout << wynik;
 
	return 0;
}

