#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int MAX = 200 * 1000;
para wej[MAX + 1];
bool uzyte[MAX + 1];
int n;
vector<pair<para, para>> wynik;

bool na_prostej(para& a, para& b, para& c) {
	return (b.second - a.second) * (c.first - b.first) == (b.first - a.first) * (c.second - b.second);
}

void wypisz(para& punkt) {
	ll a = punkt.first + 1;
	if (a > 1000 * 1000 * 1000) a = 1;
	ll b = punkt.second + 1;
	if (b > 1000 * 1000 * 1000) b = 1;
	wynik.push_back({punkt, {a, b}});
}
void wypisz(para& a, para& b) {
	wynik.push_back({a, b});
}

bool rekur(int k) {
	vector<int> punkty;
	for (int i = 1; i <= n; i++) {
		if (uzyte[i]) continue;
		punkty.push_back(i);
	}
	
	if ((int) punkty.size() <= k) {
		for (int i : punkty) {
			wypisz(wej[i]);
		}
		return true;
	}
	
	if (k == 1) {
		for (int i = 2; i < (int) punkty.size(); i++) {
			if (!na_prostej(wej[punkty[0]], wej[punkty[1]], wej[punkty[i]])) return false;
		}
		wypisz(wej[punkty[0]], wej[punkty[1]]);
		return true;
	}
	
	for (int i = 0; i < k + 1; i++) {
		for (int j = i + 1; j < k + 1; j++) {
			uzyte[punkty[i]] = true;
			uzyte[punkty[j]] = true;
			for (int h = 0; h < (int) punkty.size(); h++) {
				if (h == i || h == j) continue;
				if (na_prostej(wej[punkty[i]], wej[punkty[j]], wej[punkty[h]])) uzyte[punkty[h]] = true;
			}
			
			if (rekur(k - 1)) {
				wypisz(wej[punkty[i]], wej[punkty[j]]);
				return true;
			}
			
			for (int h = 0; h < (int) punkty.size(); h++) {
				uzyte[punkty[h]] = false;
			}
		}
	}
	
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int k;
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		wej[i] = {a, b};
	}

	if (rekur(k)) {
		cout << "TAK\n";
		while (wynik.size() < k) {
			wynik.push_back({{0, 0}, {1, 1}});
		}
		for (pair<para, para> p : wynik) {
			cout << p.first.first << " " << p.first.second << " " << p.second.first << " " << p.second.second << "\n";
		}
	} else {
		cout << "NIE";
	}

	return 0;
}

