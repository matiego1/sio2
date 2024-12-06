#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000 * 1000;
vector<pair<int, int>> graf[MAX + 1];

int roz[MAX + 1];
long long DP[MAX + 1];
long long wynik[MAX + 1];

void DFS_roz(int v, int o) {
	int wynik = 1;
	for (pair<int, int> syn : graf[v]) {
		if (syn.first != o) {
			DFS_roz(syn.first, v);
			wynik += roz[syn.first];
		}
	}
	roz[v] = wynik;
}

void DFS_DP(int v, int o) {
	for (pair<int, int> syn : graf[v]) {
		if (syn.first != o) {
			DFS_DP(syn.first, v);
			DP[v] += roz[syn.first] * syn.second + DP[syn.first];
		}
	}
}

void DFS_wynik(int v, int o, int N) {
	for (pair<int, int> syn : graf[v]) {
		if (syn.first != o) {
			wynik[syn.first] = syn.second * (N - 2 * roz[syn.first]) + wynik[v];
			DFS_wynik(syn.first, v, N);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int N;
	cin >> N;
	for (int i = 1; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].push_back(make_pair(b, c));
		graf[b].push_back(make_pair(a, c));
	}
	
	DFS_roz(1, 0);
	
	DFS_DP(1, 0);
	
	wynik[1] = DP[1];
	DFS_wynik(1, 0, N);
	
	for (int i = 1; i <= N; i++) {
		cout << wynik[i] << "\n";
	}
	
	return 0;
}