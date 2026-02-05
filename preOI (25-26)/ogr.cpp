#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 200 * 1000;
const ll MOD = 1000 * 1000 * 1000 + 7;
char wej[MAX + 1];
vector<para> grupy;
set<int> indeksy;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	int akt = 0;
	for (int i = 1; i <= m; i++) {
		cin >> wej[i];
		
		if (i > 1 && wej[i] != wej[i - 1]) {
			grupy.push_back({wej[i - 1], akt});
			akt = 0;
		}
		akt++;
	}
	grupy.push_back({wej[m], akt});
	
	for (int i = 0; i < (int) grupy.size(); i++) {
		indeksy.insert(i);
	}
	
	ll wynik = 0, sposoby = 1;
	for (int drzewo = n; drzewo >= 1; drzewo--) {
		for (auto it = indeksy.begin(); it != indeksy.end(); it++) {
			if (grupy[*it].first == 'Z') continue;
			int c = *it;
			it++;
			if (it == indeksy.end()) break;
			int z = *it;
			
			sposoby = sposoby * grupy[c].second % MOD * grupy[z].second % MOD;
			wynik += drzewo;
			
			grupy[c].second--;
			grupy[z].second--;
		}
		
		erase_if(indeksy, [](int i) {
			return grupy[i].second == 0;
		});
		for (auto it = indeksy.begin(); it != indeksy.end(); ) {
			auto nast = next(it);
			if (nast == indeksy.end()) break;
			
			int a = *it, b = *nast;
			if (grupy[a].first == grupy[b].first) {
				grupy[a].second += grupy[b].second;
				indeksy.erase(nast);
			} else {
				it++;
			}
		}
		
		if (indeksy.size() <= 1) break;
		if (indeksy.size() == 2 && grupy[*indeksy.begin()].first == 'Z') break;
	}
	
	cout << wynik << " " << sposoby << "\n";

	return 0;
}

