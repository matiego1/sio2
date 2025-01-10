#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 19;
vector<int> graf[MAX + 1];
int poziom[MAX + 1];
bool policzone[1 << (MAX + 1)];
ll dp[1 << (MAX + 1)];
int n;

ll rekur(int maska) {
	if (policzone[maska]) return dp[maska];
	policzone[maska] = true;
	
	if (maska == (1 << (n + 1)) - 1) {
		dp[maska] = 1;
		return dp[maska];
	}
	
	ll wynik = 0;
	for (int i = 0; i <= n; i++) {
		if (poziom[i] > 0) continue;
		if (maska & (1 << i)) continue;
		
		for (int u : graf[i]) {
			poziom[u]--;
		}
		
		wynik += rekur(maska | (1 << i));
		
		for (int u : graf[i]) {
			poziom[u]++;
		}
	}
	dp[maska] = wynik;
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		poziom[b]++;
	}
	
	for (int i = 1; i <= n; i++) {
		if (poziom[i] == 0) {
			graf[0].push_back(i);
			poziom[i]++;
		}
	}
	
	cout << rekur(0);

	return 0;
}

