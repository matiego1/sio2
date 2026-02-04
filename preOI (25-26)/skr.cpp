#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Wej {
	ll w, m;
};

const int MAX = 200 * 1000;
Wej wej[MAX + 1];
priority_queue<ll> kolejka;

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		wej[i] = {wczytaj(), wczytaj()};
	}
	
	sort(wej + 1, wej + 1 + n, [](Wej& w1, Wej& w2) {
		ll s1 = w1.w + w1.m;
		ll s2 = w2.w + w2.m;
		return s1 < s2;
	});
	
	int wynik = 1;
	ll masa = wej[1].m;
	kolejka.push(masa);
	for (int i = 2; i <= n; i++) {
		if (wej[i].w >= masa) {
			masa += wej[i].m;
			kolejka.push(wej[i].m);
			wynik++;
		} else {
			if (kolejka.size() && wej[i].m <= kolejka.top() && wej[i].w >= masa - kolejka.top()) {
				masa = masa - kolejka.top() + wej[i].m;
				kolejka.pop();
				kolejka.push(wej[i].m);
			}
		}
	}
	
	printf("%d", wynik);

	return 0;
}

