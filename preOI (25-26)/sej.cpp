#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int MAX_N = 200 * 1000 + 5;
const int MOD = 1000 * 1000 * 1000 + 7;

const int M1 = 1000 * 1000 * 1000 + 7;
const int M2 = 1000 * 1000 * 1000 + 696969;
const ll P1 = 997;
const ll P2 = 2137;

para suff[MAX_N];
para pref[MAX_N];
para potegi[MAX_N];

string s1, s2;
ll n, k;
vector<int> pozycje;

void pomnoz(ll m1[2][2], ll m2[2][2]) {
    ll a = ((m1[0][0] * m2[0][0]) % MOD + (m1[0][1] * m2[1][0]) % MOD) % MOD;
    ll b = ((m1[0][0] * m2[0][1]) % MOD + (m1[0][1] * m2[1][1]) % MOD) % MOD;
    ll c = ((m1[1][0] * m2[0][0]) % MOD + (m1[1][1] * m2[1][0]) % MOD) % MOD;
    ll d = ((m1[1][0] * m2[0][1]) % MOD + (m1[1][1] * m2[1][1]) % MOD) % MOD;
    m1[0][0] = a;
    m1[0][1] = b;
    m1[1][0] = c;
    m1[1][1] = d;
}

void znajdz_przesuniecie() {
	para cel = {0, 0};
	para pot = {1, 1};
	for (char c : s2) {
		cel.first = (c * pot.first % M1 + cel.first) % M1;
		cel.second = (c * pot.second % M2 + cel.second) % M2;
		pot.first = pot.first * P1 % M1;
		pot.second = pot.second * P2 % M2;
	}
	
	for (int i = (int) s1.size(); i >= 0; i--) {
		suff[i].first = suff[i + 1].first * P1 % M1;
		suff[i].second = suff[i + 1].second * P2 % M2;
		suff[i].first = (suff[i].first + s1[i]) % M1;
		suff[i].second = (suff[i].second + s1[i]) % M2;
	}
	pot = {1, 1};
	for (int i = 1; i <= (int) s1.size(); i++) {
		pref[i].first = s1[i - 1] * pot.first % M1;
		pref[i].second = s1[i - 1] * pot.second % M2;
		if (i > 0) pref[i].first = (pref[i].first + pref[i - 1].first) % M1;
		if (i > 0) pref[i].second = (pref[i].second + pref[i - 1].second) % M2;
		pot.first = pot.first * P1 % M1;
		pot.second = pot.second * P2 % M2;
	}
	
	for (int i = 0; i < (int) s1.size(); i++) {
		ll p_1 = pref[i].first * potegi[s1.size() - i].first % M1;
		ll p_2 = pref[i].second * potegi[s1.size() - i].second % M2;
		ll s_1 = suff[i].first;
		ll s_2 = suff[i].second;
		
		if (make_pair((s_1 + p_1) % M1, (s_2 + p_2) % M2) == cel) {
			pozycje.push_back(i);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	cin >> s1 >> s2;
	
	potegi[0] = {1, 1};
	for (int i = 1; i <= n; i++) {
		potegi[i].first = potegi[i - 1].first * P1 % M1;
		potegi[i].second = potegi[i - 1].second * P2 % M2;
	}
	
	if (k == 0) {
		cout << (s1 == s2);
		return 0;
	}
	if (n == 1) {
		cout << (s1 == s2);
		return 0;
	}

	znajdz_przesuniecie();
	if (pozycje.empty()) {
		cout << "0\n";
		return 0;
	}
	
	ll macierz[2][2] = {{0, 1}, {n - 1, n - 2}};
    ll wynik[2][2] = {{1, 0}, {0, 0}};

    while (k > 0) {
        if (k & 1) {
            pomnoz(wynik, macierz);
        }
        pomnoz(macierz, macierz);
        k /= 2;
    }
    
    ll w = 0;
    for (int p0 : pozycje) {
		if (p0 == 0) {
			w = (w + wynik[0][0]) % MOD;
		} else {
			w = (w + wynik[0][1]) % MOD;
		}
	}
	cout << w;

	return 0;
}
