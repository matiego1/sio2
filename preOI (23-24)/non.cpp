#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> para;

const int MAX = 1000;
int wiersze[MAX + 1];
int kolumny[MAX + 1]; 
int wej[MAX + 1][MAX + 1];
bool wziete[MAX + 1][MAX + 1];
priority_queue<para> q;
para wier[MAX + 1];
vector<para> do_dodania;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		cin >> wiersze[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> kolumny[i];
	}
	
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			char c;
			cin >> c;
			wej[x][y] = (c == '+' ? 1 : -1);
			if (c == '-') {
				wiersze[y]++;
				kolumny[x]++;
			}
		}
	}
	
	for (int i = 1; i <= m; i++) {
		if (kolumny[i] <= 0) continue;
		q.push({kolumny[i], i});
	}
	
	for (int i = 1; i <= n; i++) {
		wier[i] = {wiersze[i], i};
	}
	sort(wier + 1, wier + 1 + n);
	
	for (int i = n; i >= 1; i--) {
		while (wier[i].first--) {
			if (q.empty()) break;
			
			para kol = q.top();
			q.pop();
			
			kol.first--;
			wziete[kol.second][wier[i].second] = true;
			
			if (kol.first <= 0) continue;
			do_dodania.push_back(kol);
		}
		
		for (para p : do_dodania) {
			q.push(p);
		}
		do_dodania.clear();
	}
		
	for (int y = 1; y <= n; y++) {
		int suma = 0;
		for (int x = 1; x <= m; x++) {
			if (wziete[x][y]) suma++;
		}
		if (suma != wiersze[y]) {
			cout << "NIE";
			return 0;
		}
	}
	
	for (int x = 1; x <= m; x++) {
		int suma = 0;
		for (int y = 1; y <= n; y++) {
			if (wziete[x][y]) suma++;
		}
		if (suma != kolumny[x]) {
			cout << "NIE";
			return 0;
		}
	}
	
	cout << "TAK\n";
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			bool wynik = wziete[x][y];
			if (wej[x][y] == -1) wynik = !wynik; 
			cout << (wynik ? "#" : ".");
		}
		cout << "\n";
	}
	return 0;
}
