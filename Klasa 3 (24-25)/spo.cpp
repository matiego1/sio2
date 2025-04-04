#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
vector<int> graf[MAX];
vector<int> graf2[MAX];
bool odwie[MAX];
int order[MAX];
int sklad[MAX];
int wynik[MAX];
int t = 0;


void dodaj(int a, int b) {
	graf[a ^ 1].push_back(b);
	graf[b ^ 1].push_back(a);
	graf2[b].push_back(a ^ 1);
	graf2[a].push_back(b ^ 1);
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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		int a = 2 * i - 1;
		int b = 2 * i;
		
		dodaj(2 * a, 2 * b);
		dodaj(2 * a ^ 1, 2 * b ^ 1);
	}
	
	while (m--) {
		int a, b;
		cin >> a >> b;
		dodaj(2 * a ^ 1, 2 * b ^ 1);
	}
	
	policz_sss();
	
	for (int i = 1; i <= 2 * n; i++) {
		if (sklad[2 * i] == sklad[2 * i ^ 1]) {
			cout << "NIE";
			return 0;
		}
		wynik[i] = (sklad[2 * i] > sklad[2 * i ^ 1]);
	}
	
	for (int i = 1; i <= 2 * n; i++) {
		if (wynik[i]) {
			cout << i << "\n";
		}
	}

	return 0;
}
