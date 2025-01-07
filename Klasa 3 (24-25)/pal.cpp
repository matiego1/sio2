#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll MOD = 1000 * 1000 * 1000 + 7;
const ll P = 29;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	ll przod = 0, tyl = 0;
	ll potega = 1;
	char c;
	for (int i = 1; cin.get(c); i++) {
		if (!('a' <= c && c <= 'z')) continue;
		przod = (przod * P + c - 'a') % MOD;
		tyl = (tyl + potega * (c - 'a') % MOD) % MOD;
		potega = potega * P % MOD;
	}
	
	cout << (przod == tyl ? "TAK" : "NIE");

	return 0;
}

