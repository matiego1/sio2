#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef pair<int, int> para;

const int K = 450;
const int MAX = 200 * 1000;
vector<int> graf[MAX + 1];
vector<para> krawedzie;
vector<int> duze;
bool male[MAX + 1];
bool polaczone[MAX + 1];

void wczytaj_inty(int& a, int& b) {
	int znak;
	while ((znak = getchar()) != ' ') {
		a = 10 * a + znak - '0';
	}
	while ((znak = getchar()) != '\n') {
		b = 10 * b + znak - '0';
	}
}

int main() {
	int n = 0, m = 0;
	wczytaj_inty(n, m);
	
	for (int i = 1; i <= m; i++) {
		int a = 0, b = 0;
		wczytaj_inty(a, b);
		
		krawedzie.push_back({a, b});
		
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	for (int i = 1; i <= n; i++) {
		if ((int) graf[i].size() >= K) {
			duze.push_back(i);
		} else {
			male[i] = true;
		}
	}
	
	int wynik1 = 0, wynik2 = 0, wynik3 = 0;
	for (int v : duze) {
		for (int u : graf[v]) {
			polaczone[u] = true;
		}
		for (para kraw : krawedzie) {
			if (!polaczone[kraw.first]) continue;
			if (!polaczone[kraw.second]) continue;
			
			int ile = 1;
			if (!male[kraw.first]) ile++;
			if (!male[kraw.second]) ile++;
			if (ile == 1) {
				wynik1++;
			} else if (ile == 2) {
				wynik2++;
			} else {
				wynik3++;
			}
		}
		for (int u : graf[v]) {
			polaczone[u] = false;
		}
	}
	
	int wynik_male = 0;
	for (para kraw : krawedzie) {
		if (!male[kraw.first]) continue;
		if (!male[kraw.second]) continue;
		
		for (int v : graf[kraw.second]) {
			if (!male[v]) continue;
			polaczone[v] = true;
		}
		for (int v : graf[kraw.first]) {
			if (polaczone[v]) {
				wynik_male++;
			}	
		}
		for (int v : graf[kraw.second]) {
			polaczone[v] = false;
		}
	}
	
	printf("%d", wynik1 + (wynik2 / 2) + (wynik3 / 3) + (wynik_male / 3));

	return 0;
}
