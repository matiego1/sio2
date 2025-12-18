#include "rowlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll MAX_ai = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;
vector<ll> tab;

ll podzadanie1(int n) {
	ll pocz = 0, kon = MAX_ai;
	while ((int) tab.size() < n) {
		ll mini, maks;
		ZapytajChrisa(pocz, kon, mini, maks);
		tab.push_back(mini);
		if (mini < maks) tab.push_back(maks);
		pocz = mini + 1;
		kon = maks - 1;
	}
	
	sort(tab.begin(), tab.end());
	
	ll maks = -1;
	for (int i = 0; i < (int) tab.size() - 1; i++) {
		maks = max(maks, tab[i + 1] - tab[i]);
	}
	return maks;
}

ll sufit(ll a, ll b) {
	if (a % b == 0) return a / b;
	return a / b + 1;
}

ll podzadanie2(int n) {
	ll minimum, maksimum;
	ZapytajChrisa(0, MAX_ai, minimum, maksimum);
	
	if (n == 2) return maksimum - minimum;
	
	ll przedzial = sufit(maksimum - minimum, n);
	
	tab.push_back(minimum);
	for (ll pocz = minimum + 1; pocz <= maksimum - 1; pocz += przedzial) {
		ll kon = min(maksimum - 1, pocz + przedzial - 1);
		
		ll mini, maks;
		ZapytajChrisa(pocz, kon, mini, maks);
		
		if (mini == -1) continue;
		tab.push_back(mini);
		tab.push_back(maks);
	}
	tab.push_back(maksimum);

	ll maks = 0;
	for (int i = 0; i <= (int) tab.size() - 2; i += 2) {
		maks = max(maks, tab[i + 1] - tab[i]);	
	}
	return maks;
}

ll ZnajdzSkarpe(int T, int N) {
    if (T == 1) {
    	return podzadanie1(N);
	} else {
		return podzadanie2(N);
	}
}
