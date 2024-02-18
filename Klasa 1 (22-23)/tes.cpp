#include <iostream>
#include <set>
using namespace std;

const int MAX = 1000 * 1000;
set<int> indeks[MAX + 5];
int wej[MAX + 5];

bool rozwiaz() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> wej[i];
	}
	
	int minimum = -1;
	for (int i = 0; i < n; i++) {
		if (indeks[wej[i]].size() == 0) {
			return false; //nie ma takiej liczby w ci¹gu
		}
		
		auto x = indeks[wej[i]].upper_bound(minimum);
		if (x == indeks[wej[i]].end()) {
			return false; //wszystkie liczby ju¿ wykorzystane
		}
		
		minimum = *x;
	}
	
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
		
	int m;
	cin >> m;
	
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		indeks[a].insert(i);
	}
	
	int q;
	cin >> q;
	while (q--) {
		cout << (rozwiaz() ? "TAK\n" : "NIE\n");
	}

	return 0;
}

