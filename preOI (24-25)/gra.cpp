#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
vector<vector<int>> wej;
vector<vector<int>> zysk;
vector<vector<para>> kolejnosc;
int indeks[MAX + 1];
ll wart[MAX + 1];
int ile[MAX + 1];
queue<int> kolejka;

int n, k;
int wynik = 0;

void rozszerz(int karta) {
	while (indeks[karta] <= n) {
		int osoba = kolejnosc[karta][indeks[karta]].second;

		if (wej[osoba][karta] <= wart[karta]) {
			ile[osoba]++;
			if (ile[osoba] == k) {
				kolejka.push(osoba);
			}
			
			indeks[karta]++;
		} else break;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	
	wej.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		wej[i].resize(k + 1);
		for (int j = 1; j <= k; j++) {
			cin >> wej[i][j];
		}
	}
	zysk.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		zysk[i].resize(k + 1);
		for (int j = 1; j <= k; j++) {
			cin >> zysk[i][j];
		}
	}
	
	kolejnosc.resize(k + 1);
	for (int karta = 1; karta <= k; karta++) {
		kolejnosc[karta].resize(n + 1);
		for (int j = 1; j <= n; j++) kolejnosc[karta][j] = {wej[j][karta], j};
		
		sort(kolejnosc[karta].begin(), kolejnosc[karta].end());
	}
	
	for (int karta = 1; karta <= k; karta++) {
		indeks[karta] = 1;
		rozszerz(karta);
	}
	
	while (kolejka.size()) {
		int osoba = kolejka.front();
		kolejka.pop();
		
		wynik++;
		for (int karta = 1; karta <= k; karta++) {
			wart[karta] += zysk[osoba][karta];
			rozszerz(karta);
		}
	}
	
	cout << wynik;

	return 0;
}
