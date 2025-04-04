#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX_N = 150 * 1000;
const int PREF = MAX_N;
const int SUF = 2 * MAX_N;
const int MAX = 6 * MAX_N + 10;
vector<int> graf[MAX];
vector<int> graf2[MAX];
bool odwie[MAX];
int order[MAX];
int sklad[MAX];
int wej[MAX];
pair<para, int> walki[MAX];
int t = 0;

void dodaj(int a, int b) {
	graf[a ^ 1].push_back(b);
	graf[b ^ 1].push_back(a);
	graf2[b].push_back(a ^ 1);
	graf2[a].push_back(b ^ 1);
}

void impl(int a, int b, int zaprzecz_b) {
	dodaj(2 * a ^ 1, 2 * b ^ zaprzecz_b);
}

void dfs(int v) {
	odwie[v] = true;
	for (int u : graf[v]) {
		if (odwie[u]) continue;
		dfs(u);
	}
	order[++t] = v;
}

void sss(int v) {
	odwie[v] = true;
	sklad[v] = t;
	for (int u : graf2[v]) {
		if (odwie[u]) continue;
		sss(u);
	}
}

void policz_sss() {
	t = 0;
	for (int i = 1; i < MAX; i++) odwie[i] = false;
	for (int i = 1; i < MAX; i++) {
		if (odwie[i]) continue;
		dfs(i);
	}
	
	t = 0;
	for (int i = 1; i < MAX; i++) odwie[i] = false;
	for (int i = MAX - 1; i >= 1; i--) {
		if (odwie[order[i]]) continue;
		t++;
		sss(order[i]);
	}
}

void policz(int pocz, int kon) {
	if (pocz == kon) return;
	
	impl(PREF + pocz, walki[pocz].second, 1);
	for (int i = pocz + 1; i <= kon; i++) {
		impl(PREF + i, PREF + i - 1, 0);
		impl(PREF + i, walki[i].second, 1);
	}
	
	impl(SUF + kon, walki[kon].second, 1);
	for (int i = kon - 1; i >= pocz; i--) {
		impl(SUF + i, SUF + i + 1, 0);
		impl(SUF + i, walki[i].second, 1);
	}
	
	impl(walki[pocz].second, SUF + pocz + 1, 0);
	for (int i = pocz + 1; i < kon; i++) {
		impl(walki[i].second, PREF + i - 1, 0);
		impl(walki[i].second, SUF + i + 1, 0);
	}
	impl(walki[kon].second, PREF + kon - 1, 0);
}

bool rozwiaz() {
	for (int i = 1; i < MAX; i++) {
		graf[i].clear();
		graf2[i].clear();
	}
	
	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	dodaj(2 * 1, 2 * 1);
	dodaj(2 * (n - 1), 2 * (n - 1));
	
	for (int i = 1; i < n - 1; i++) {
		dodaj(2 * i, 2 * (i + 1));
	}
	
	for (int i = 1; i < n; i++) {
		walki[i] = {{wej[i], wej[i + 1]}, i};
	}
	sort(walki + 1, walki + n);
	
	int pocz = 1;
	for (int i = 2; i < n; i++) {
		if (walki[i - 1].first != walki[i].first) {
			policz(pocz, i - 1);
			pocz = i;
		}
	}
	policz(pocz, n - 1);
	
	policz_sss();
	
	for (int i = 1; i < n; i++) {
		if (sklad[2 * i] == sklad[2 * i ^ 1]) return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int testy;
	cin >> testy;
	
	while (testy--) {
		cout << (rozwiaz() ? "TAK" : "NIE") << "\n";
	}

	return 0;
}
