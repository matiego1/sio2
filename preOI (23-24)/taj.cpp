#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
int typ[MAX + 1];
vector<int> graf[MAX + 1];
pair<int, para> dp[MAX + 1];
vector<para> wynik;

bool dfs(int v, int ojciec, int glebokosc) {
	vector<para> rowno, nizej, wyzej;
	
	// Wartosci od dzieci
	for (int u : graf[v]) {
		if (u == ojciec) continue;
		if (!dfs(u, v, glebokosc + 1)) {
			return false;	
		}
		if (dp[u].first == 1) {
			rowno.push_back(dp[u].second);
		} else if (dp[u].first == 2) {
			nizej.push_back(dp[u].second);
		} else if (dp[u].first == 3) {
			wyzej.push_back(dp[u].second);
		}
	}
	
	// Wlasna wartosc
	if (typ[v] == 1) {
		rowno.push_back({glebokosc, v});
	} else if (typ[v] == 2) {
		nizej.push_back({glebokosc, v});
	} else if (typ[v] == 3) {
		wyzej.push_back({glebokosc, v});
	}
	
	// Sortowanie po glebokosciach
	sort(rowno.begin(), rowno.end());
	sort(nizej.begin(), nizej.end());
	sort(wyzej.begin(), wyzej.end());
	
	int ile_wolnych = (rowno.size() % 2) + abs((int) (nizej.size() - wyzej.size()));
	if (ile_wolnych > 1) return false;
	if (v == 1 && ile_wolnych > 0) return false;
	
	bool ustawione = false;
	// Sprawdz rowne
	for (int i = 0; i < (int) rowno.size(); i++) {
		if (i + 1 < (int) rowno.size() && rowno[i].first == rowno[i + 1].first) {
			wynik.push_back({rowno[i].second,rowno[i+1].second});
			i++;
			continue;
		}
		
		if (rowno.size() % 2 == 0) return false;
		if (ustawione) return false;
		
		dp[v] = {1, rowno[i]};
		ustawione = true;
	}
	
	// a) Do dp wierzcholek nizej?
	if (nizej.size() > wyzej.size()) {
		int in = nizej.size() - 1, iw = wyzej.size() - 1;
		while (in >= 0 && iw >= 0) {
			if (nizej[in].first < wyzej[iw].first) {
				wynik.push_back({nizej[in].second, wyzej[iw].second});
				iw--;
			} else {
				if (ustawione) return false;
				
				dp[v] = {2, nizej[in]};
				ustawione = true;
			}
			in--;
		} 
		
		if (ustawione) return true;
		dp[v] = {2, nizej[0]};
		return true;
	}
	
	// b) Do dp wierzcholek wyzej? albo zaden
	int in = 0, iw = 0;
	while (in < (int) nizej.size() && iw < (int) wyzej.size()) {
		if (nizej[in].first < wyzej[iw].first) {
			wynik.push_back({nizej[in].second, wyzej[iw].second});
			in++;
		} else {
			if (nizej.size() == wyzej.size()) return false;
			if (ustawione) return false;
			
			dp[v] = {3, wyzej[iw]};
			ustawione = true;
		}
		iw++;
	}
	if (wyzej.size() == nizej.size()) return true;
	if (ustawione) return true;
	dp[v] = {3, wyzej[wyzej.size() - 1]};
	
	return true;
}

int main() {
	int n;
	scanf("%d", &n);
	
	int ile1 = 0, ile23 = 0;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &typ[i]);
		if (typ[i] == 1) {
			ile1++;
		} else if (typ[i] == 2) {
			ile23++;
		} else if (typ[i] == 3) {
			ile23--;
		}
	}
	
	if (ile1 % 2 != 0 || ile23 != 0) {
		printf("NIE");
		return 0;
	}
	
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	if (!dfs(1, 1, 1)) {
		printf("NIE");
		return 0;
	}
	
	printf("TAK\n");
	for (para p : wynik) {
		printf("%d %d\n", p.first, p.second);
	}	
}
