#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, int> para;

const int MAX = 2 * 1000 * 1000;
const int R = (1 << 21);
int wej[MAX + 1];
ll pref[MAX + 1];
ll deski[MAX + 1];
priority_queue<para> q;

ll suma_pref(int pocz, int kon) {
	if (pocz > kon) return 0;
	return pref[kon] - pref[pocz - 1];
}

ll get(int lewy) {
	if (q.empty()) return 0;
	para p;
	while ((p = q.top()).second < lewy) {
		q.pop();
		if (q.empty()) return 0;
	}
	return p.first;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, d;
	ll p;
	cin >> n >> p >> d;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		pref[i] = pref[i - 1] + wej[i];
	}
	
	for (int i = 1; i <= n - d + 1; i++) {
		deski[i] = suma_pref(i, i + d - 1);
	}
	
	int wynik = d;
	
	ll dolki = 0;
	int lewy = 1;
	for (int prawy = 1; prawy <= n; prawy++) {
		dolki += wej[prawy];
		
		int nowy = prawy - d + 1;
		if (nowy >= 1) {
			q.push({deski[nowy], nowy});
		}
		
		while (lewy + d < prawy && dolki - get(lewy) > p) {
			dolki -= wej[lewy];
			lewy++;
		}
		
		if (dolki - get(lewy) <= p) {
			wynik = max(wynik, prawy - lewy + 1);
		}
	}
	
	cout << wynik;

	return 0;
}


