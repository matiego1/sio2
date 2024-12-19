#include <iostream>
#include <map>
using namespace std;

const int MAX = 100 * 1000;
int kra[MAX + 1];
map<int, int> sila[MAX + 1];

int findd(int x) {
    if (x == kra[x]) return x;
    kra[x] = findd(kra[x]);
    return kra[x];
}
void unionn(int a, int b) {
    a = findd(a);
    b = findd(b);
    if (a == b) return;
    
    if (sila[a].size() >= sila[b].size()) {
    	kra[b] = a;
    	for (pair<int, int> i : sila[b]) {
    		sila[a][i.first] += i.second;
		}
	} else {
		kra[a] = b;
		for (pair<int, int> i : sila[a]) {
			sila[b][i.first] += i.second;
		}
	}
    
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		sila[i][a] = 1;
		kra[i] = i;
	}
	
	while (q--) {
		char c;
		cin >> c;
		int a, b;
		cin >> a >> b;
		
		if (c == 'D') {
			unionn(a, b);
		} else {
			cout << sila[findd(a)][b] << "\n";
		}
	}

	return 0;
}