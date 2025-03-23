#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
int rozmiar[MAX + 1];
int przejscia[MAX + 1];
int wyniki[MAX + 1];
queue<int> q;
vector<int> kolej;

void dfs_rozmiar(int v, int p) {
	rozmiar[v] = 1;
	for (int u : graf[v]) {
		if (u == p) continue;
		dfs_rozmiar(u, v);
		rozmiar[v] += rozmiar[u];
	}
}

int dfs_centroid(int v, int p, int n) {
	for (int u : graf[v]) {
		if (u == p) continue;
		if (rozmiar[u] > n / 2) {
			return dfs_centroid(u, v, n);
		}
	}
	return v;
}

void dfs_przejscia(int v, int p, int n) {
	for (int u : graf[v]) {
		if (u == p) continue;
		przejscia[v] += min(n - rozmiar[u], rozmiar[u]);
		dfs_przejscia(u, v, n);
	}
}

void dfs_order(int v, int p) {
    q.push(v);
    kolej.push_back(v);
    for (int u : graf[v]) {
        if (u == p) continue;
        dfs_order(u, v);
    }
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	dfs_rozmiar(1, 1);
	dfs_przejscia(1, 1, rozmiar[1]);
	int centroid = dfs_centroid(1, 1, rozmiar[1]);
	dfs_order(centroid, centroid);

	ll wynik = 0;
	for (int i = 1; i <= n; i++) {
		wynik += przejscia[i];
	}
	cout << 2 * wynik << "\n";

    for (int i = 1; i <= n / 2; i++) {
        q.push(q.front());
        q.pop();
    }

    int i = 0;
    while (q.size()) {
        wyniki[kolej[i++]] = q.front();
        q.pop();
    }

    for (int i = 1; i <= n; i++) {
        cout << wyniki[i] << " ";
    }

	return 0;
}