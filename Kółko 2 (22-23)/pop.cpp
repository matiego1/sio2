#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
int poziom[MAX + 1];
map<int, int> zlicz;
string wej;

ll rekur(int pocz, int kon) {
	if (pocz == kon) return 0;

	int srodek = (pocz + kon) / 2;
	ll wynik = rekur(pocz, srodek) + rekur(srodek + 1, kon);
	
	zlicz.clear();
	int mini = INT_MAX;
	for (int i = srodek + 1; i <= kon; i++) {
		mini = min(mini, poziom[i]);
		if (wej[i] == ')' && poziom[i] == mini) {
			zlicz[poziom[i]]++;
		}
	}
	
	mini = INT_MAX;	
	for (int i = srodek; i >= pocz; i--) {
		mini = min(mini, poziom[i]);
		if (mini < poziom[i] - 1) continue;
		if (wej[i] == '(') {
			wynik += zlicz[poziom[i] - 1];
		}
	}
	
	return wynik;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n >> wej;
	wej = "$" + wej;
	
	for (int i = 1; i <= n; i++) {
		poziom[i] = poziom[i - 1] + (wej[i] == '(' ? 1 : -1); 
	}
	
	cout << rekur(1, n);

	return 0;
}
