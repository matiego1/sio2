#include <iostream>

#include <set>

using namespace std;

typedef long long ll;

typedef pair<ll, ll> para;



const int MAX = 100 * 1000;

const ll P1 = 15671;

const ll MOD1 = 1000 * 1000 * 1000 + 7;

const ll P2 = 45377;

const ll MOD2 = 1000012309;

ll potega_p1[MAX + 1];

ll potega_p2[MAX + 1];



string wej;

int n;



set<para> fragmenty;



para hashuj(string& s) {

	ll hash1 = 0, hash2 = 0;

	for (int i = 0; i < s.length(); i++) {

		hash1 = (hash1 * P1 + s[i]) % MOD1;

		hash2 = (hash2 * P2 + s[i]) % MOD2;

	}

	return make_pair(hash1, hash2);

} 



void rozwiaz() {

	int z;

	cin >> z;

	if (z <= 0) return;

	

	string s;

	cin >> s;

	int m = s.length();

	if (m > n) return;

	

	fragmenty.clear();

	

	ll hash1 = 0, hash2 = 0;

	//pierwszy hash

	for (int i = 0; i < m; i++) {

		hash1 = (hash1 * P1 + wej[i]) % MOD1;

		hash2 = (hash2 * P2 + wej[i]) % MOD2;

	}

	fragmenty.insert(make_pair(hash1, hash2));

	

	//kolejne hashe

	for (int i = m; i < n; i++) {

		hash1 = (hash1 - (wej[i - m] * potega_p1[m - 1]) % MOD1 + MOD1) % MOD1;

		hash1 = (hash1 * P1 + wej[i]) % MOD1;

		

		hash2 = (hash2 - (wej[i - m] * potega_p2[m - 1]) % MOD2 + MOD2) % MOD2;

		hash2 = (hash2 * P2 + wej[i]) % MOD2;

		

		fragmenty.insert(make_pair(hash1, hash2));

	}

	

	if (fragmenty.find(hashuj(s)) == fragmenty.end()) {

		cout << "NIE\n";

	} else {

		cout << "OK\n";

	}

	z--;

	

	while (z--) {

		cin >> s;

		if (fragmenty.find(hashuj(s)) == fragmenty.end()) {

			cout << "NIE\n";

		} else {

			cout << "OK\n";

		}	

	}

}



int main() {

	ios_base::sync_with_stdio(0);

	cin.tie(0);

	

	potega_p1[0] = 1;

	potega_p2[0] = 1;

	for (int i = 1; i <= MAX; i++) {

		potega_p1[i] = (potega_p1[i - 1] * P1) % MOD1;

		potega_p2[i] = (potega_p2[i - 1] * P2) % MOD2;

	}

	

	cin >> wej;

	n = wej.length();

	

	int k;

	cin >> k;

	

	while (k--) {

		rozwiaz();

	}



	return 0;

}

