#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef long double ld;
typedef pair<ll, ll> para;

const int MAX = 60 * 1000;
const ll INF = LLONG_MAX;
const int PREC = 1000 * 1000;
ll poz[MAX + 1];
ll pred[MAX + 1];
para przedzialy[MAX + 1];
int n;

para iloczyn(para p1, para p2) {
	if (p1.first == 1 && p1.second == -1) return {1, -1};
	if (p2.first == 1 && p2.second == -1) return {1, -1};
	ll tab[4] = {p1.first, p1.second, p2.first, p2.second};
	sort(tab, tab + 4);
	int ile[3] = {0, 0, 0};
	for (int i = 0; i <= 2; i++) {
		ll pkt = (tab[i] + tab[i + 1]) / 2;
		if (p1.first <= pkt && pkt <= p1.second) ile[i]++;
		if (p2.first <= pkt && pkt <= p2.second) ile[i]++;
	}
	ll pocz = 1, kon = -1;
	for (int i = 0; i <= 2; i++) {
		if (ile[i] == 2) {
			pocz = tab[i];
			break;
		}
	}
	for (int i = 2; i >= 0; i--) {
		if (ile[i] == 2) {
			kon = tab[i + 1];
			break;
		}
	}
	return {pocz, kon};
}

bool sprawdz(ll czas) {
	for (int i = 1; i <= n; i++) {
		ll pocz = poz[i] - czas * pred[i];
		ll kon = poz[i] + czas * pred[i];
		przedzialy[i] = {pocz, kon};
	}
	
	for (int i = 2; i <= n; i++) {
		przedzialy[1] = iloczyn(przedzialy[1], przedzialy[i]);
	}
	
	return (przedzialy[1].first <= przedzialy[1].second);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cout.precision(6);
	cout << fixed;

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		long long a;
		cin >> a;
		poz[i] = a * PREC;;
	}
	for (int i = 1; i <= n; i++) {
		long long a;
		cin >> a;
		pred[i] = a;
	}
	
	ll pocz = 0, kon = 1000ll * 1000 * 1000 * PREC;
	while (pocz < kon) {
		ll srodek = (pocz + kon) / 2;
		if (sprawdz(srodek)) {
			kon = srodek;
		} else {
			pocz = srodek + 1;
		}
	}
	cout << ((ld) pocz) / PREC;

	return 0;
}

