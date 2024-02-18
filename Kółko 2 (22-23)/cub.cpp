#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int MAX = 1000;
const ll P1 = 15671;
const ll Q1 = 45377;
const ll MOD1 = 1000 * 1000 * 1000 + 7;
const ll P2 = 16369;
const ll Q2 = 46183;
const ll MOD2 = 1000012309;

para pref1[MAX + 1][MAX + 1];
para pref2[MAX + 1][MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int nx, ny, mx, my;
	cin >> nx >> ny >> mx >> my;
	
	ll potega_p1 = 1, potega_p2 = 1;
	for (int i = 0; i < mx; i++) {
		potega_p1 = (potega_p1 * P1) % MOD1;
		potega_p2 = (potega_p2 * P2) % MOD2;
	}
	ll potega_q1 = 1, potega_q2 = 1;;
	for (int i = 0; i < my; i++) {
		potega_q1 = (potega_q1 * Q1) % MOD1;
		potega_q2 = (potega_q2 * Q2) % MOD2;
	}
	
	for (int y = 1; y <= ny; y++) {
		for (int x = 1; x <= nx; x++) {
			int a;
			cin >> a;
			pref1[x][y].first = a;
			pref1[x][y].first = (pref1[x][y].first + pref1[x - 1][y].first * P1) % MOD1;
			pref1[x][y].first = (pref1[x][y].first + pref1[x][y - 1].first * Q1) % MOD1;
			pref1[x][y].first = (pref1[x][y].first - ((((pref1[x - 1][y - 1].first * P1) % MOD1) * Q1) % MOD1) + MOD1) % MOD1;
			
			pref1[x][y].second = a;
			pref1[x][y].second = (pref1[x][y].second + pref1[x - 1][y].second * P2) % MOD2;
			pref1[x][y].second = (pref1[x][y].second + pref1[x][y - 1].second * Q2) % MOD2;
			pref1[x][y].second = (pref1[x][y].second - ((((pref1[x - 1][y - 1].second * P2) % MOD2) * Q2) % MOD2) + MOD2) % MOD2;
		}
	}
	
	for (int y = 1; y <= my; y++) {
		for (int x = 1; x <= mx; x++) {
			int a;
			cin >> a;
			pref2[x][y].first = a;
			pref2[x][y].first = (pref2[x][y].first + pref2[x - 1][y].first * P1) % MOD1;
			pref2[x][y].first = (pref2[x][y].first + pref2[x][y - 1].first * Q1) % MOD1;
			pref2[x][y].first = (pref2[x][y].first - ((((pref2[x - 1][y - 1].first * P1) % MOD1) * Q1) % MOD1) + MOD1) % MOD1;
			
			pref2[x][y].second = a;
			pref2[x][y].second = (pref2[x][y].second + pref2[x - 1][y].second * P2) % MOD2;
			pref2[x][y].second = (pref2[x][y].second + pref2[x][y - 1].second * Q2) % MOD2;
			pref2[x][y].second = (pref2[x][y].second - ((((pref2[x - 1][y - 1].second * P2) % MOD2) * Q2) % MOD2) + MOD2) % MOD2;
		}
	}
	
	int wynik = 0;
	for (int y = my; y <= ny; y++) {
		for (int x = mx; x <= nx; x++) {
			ll hash1 = pref1[x][y].first;
			hash1 = (hash1 - ((pref1[x - mx][y].first * potega_p1) % MOD1) + MOD1) % MOD1;
			hash1 = (hash1 - ((pref1[x][y - my].first * potega_q1) % MOD1) + MOD1) % MOD1;
			hash1 = (hash1 + ((pref1[x - mx][y - my].first * potega_p1) % MOD1) * potega_q1) % MOD1;
			
			ll hash2 = pref1[x][y].second;
			hash2 = (hash2 - ((pref1[x - mx][y].second * potega_p2) % MOD2) + MOD2) % MOD2;
			hash2 = (hash2 - ((pref1[x][y - my].second * potega_q2) % MOD2) + MOD2) % MOD2;
			hash2 = (hash2 + ((pref1[x - mx][y - my].second * potega_p2) % MOD2) * potega_q2) % MOD2;
			
			if (make_pair(hash1, hash2) == pref2[mx][my]) {
				wynik++;
			}
		}
	}
	
	cout << wynik;

	return 0;
}

