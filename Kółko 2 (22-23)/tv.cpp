#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;

struct Punkt {
	int x, y;
};
Punkt make_punkt(int x, int y) {
	return {x, y};
}

const ll INF = 9ll * 1000 * 1000 * 1000 * 1000 * 1000 * 1000;
const int MAX = 5000;
int n;
Punkt wej[MAX + 1];
int kra[MAX + 1];
ll mini_odleg[MAX + 1];

int findd(int x) {
	if (x == kra[x]) return x;
	kra[x] = findd(kra[x]);
	return kra[x];
}

void unionn(int a, int b) {
	a = findd(a);
	b = findd(b);
	if (a == b) return;
	kra[b] = a;
}

ll odleg(Punkt& a, Punkt& b) {
	ll x1 = a.x - b.x;
	ll x2 = a.y - b.y;
	return ceill(sqrtl(x1 * x1 + x2 * x2));
}

void aktualizuj_odleglosci(int punkt) {
	for (int i = 1; i <= n; i++) {
		mini_odleg[i] = min(mini_odleg[i], odleg(wej[punkt], wej[i]));
	}
}

pair<int, ll> najblizszy_punkt(int punkt) {
	aktualizuj_odleglosci(punkt);
	int wynik = punkt;
	ll mini = INF;
	for (int i = 1; i <= n; i++) {
		if (mini_odleg[i] > 0 && mini_odleg[i] < mini) {
			mini = mini_odleg[i];
			wynik = i;
		}
	}
	return make_pair(wynik, mini);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		wej[i] = make_punkt(a, b);
		kra[i] = i;
		mini_odleg[i] = INF;
	}
	
	int punkt = 1;
	ll maks = 0;
	for (int i = 1; i <= n; i++) {
		pair<int, ll> nastepny = najblizszy_punkt(punkt);
		unionn(punkt, nastepny.first);
		if (nastepny.second != INF) {
			maks = max(maks, nastepny.second);
		}
		punkt = nastepny.first;
	}
	
	cout << maks * (n - 1);

	return 0;
}

