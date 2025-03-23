#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int R = (1 << 17);
const int MAX_M = 200 * 1000;
const int MAX_WART = 1000 * 1000 * 1000;

const int ZAPYT = 2 * R;
const int MAX = 2 * R + MAX_M + 1;

vector<para> graf[MAX];
vector<int> graf2[MAX];
int wart[MAX];
int poziom[MAX];
queue<int> q;

void polacz(int pocz, int kon, int v) {
	pocz += R - 1;
	kon += R + 1;
	while (pocz / 2 != kon / 2) {
		if (pocz % 2 == 0) {
			graf[v].push_back({pocz + 1, 0});
			graf2[pocz + 1].push_back(v);
		}
		if (kon % 2 == 1) {
			graf[v].push_back({kon - 1, 0});
			graf2[kon - 1].push_back(v);
		}
		pocz /= 2;
		kon /= 2;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, s, m;
	cin >> n >> s >> m;
	
	for (int i = 1; i < MAX; i++) {
		wart[i] = -1;
	}
	for (int i = 1; i <= s; i++) {
		int a;
		cin >> a;
		cin >> wart[R + a];
	}
	
	for (int i = R - 1; i >= 1; i--) {
		graf[i].push_back({2 * i, 0});
		graf2[2 * i].push_back(i);
		graf[i].push_back({2 * i + 1, 0});
		graf2[2 * i + 1].push_back(i);
	}
	
	for (int i = 1; i <= m; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		
		int pocz = l;
		
		for (int j = 1; j <= k; j++) {
			int x;
			cin >> x;
			
			if (pocz <= x - 1) {
				polacz(pocz, x - 1, ZAPYT + i);
			}
			pocz = x + 1;
			
			graf[R + x].push_back({ZAPYT + i, 1});
			graf2[ZAPYT + i].push_back(R + x);
		}
		
		if (pocz <= r) {
			polacz(pocz, r, ZAPYT + i);
		}
	}
	
	for (int i = 1; i < MAX; i++) {
		poziom[i] = (int) graf[i].size();
		if (poziom[i] <= 0) {
			q.push(i);
		}
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		for (int u : graf2[v]) {
			poziom[u]--;
			if (poziom[u] <= 0) {
				q.push(u);
			}
		}
		
		int maks = 1;
		for (para p : graf[v]) {
			maks = max(maks, wart[p.first] + p.second);
		}
		
		if (maks > MAX_WART) {
			cout << "NIE";
			return 0;
		}
		
		if (wart[v] == -1) {
			wart[v] = maks;
		} else if (maks > wart[v]) {
			cout << "NIE";
			return 0;
		}
	}
	
	for (int i = 1; i < MAX; i++) {
		if (poziom[i] != 0) {
			cout << "NIE\n";
			return 0;
		}
	}
	
	cout << "TAK\n";
	for (int i = R + 1; i <= R + n; i++) {
		cout << wart[i] << " ";
	}

	return 0;
}
