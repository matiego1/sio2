#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int P = 353879;//1259689; //https://www.algorytm.edu.pl/images/prim100000.txt
const long long MOD = 1000 * 1000 * 1000 + 9;
const int MAX = 1000 * 1000;

long long potegi[MAX + 3];
long long pref[MAX + 3];

long long znak(char c) {
	return c - 'a' + 1;
}

int hashPref(int L, int R) {
	R += 1;
	L += 1;
	return (pref[R] - ((pref[L - 1] * potegi[R - L + 1]) % MOD) + MOD) % MOD;
}

bool sprawdz(int n, int m, int hash) {
	for (int i = 1; i < n - m; i++) {
		if (hashPref(i, i + m - 1) == hash) return true;
	}
	return false;
}

int main() {
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	
	long long akt = 1;
	for (int i = 0; i <= MAX; i++) {
		potegi[i] = akt;
		akt = (akt * P) % MOD;
	}
	
	int n;
	cin >> n;
	string wej;
	cin >> wej;
	
	pref[0] = 0;
	for (int i = 1; i <= n; i++) {
		pref[i] = (pref[i - 1] * P + znak(wej[i - 1])) % MOD;
	}
	
	vector<pair<int, int>> kandy;
	kandy.push_back(make_pair(0, 0));
	for (int i = 0; i < n - 1; i++) {
		if (hashPref(0, i) == hashPref(n - i - 1, n - 1)) {
			kandy.push_back(make_pair(i + 1, hashPref(0, i)));
		}
	}
	
	int lewy = 0, prawy = kandy.size() - 1;
	while (lewy < prawy) {
		int srodek = (lewy + prawy + 1) / 2;
		if (kandy[srodek].first == 0) {
			cout << 0;
			return 0;
		}
		if (sprawdz(n, kandy[srodek].first, kandy[srodek].second)) {
			lewy = srodek;
		} else {
			prawy = srodek - 1;
		}
	}
	cout << kandy[lewy].first;
	
	return 0;
}
