#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1005;
para wej[MAX];
char ciag[MAX];
int cel[MAX];
vector<int> wierz;
vector<int> wierz_cyklu;
bool odwie[MAX];

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(), m = wczytaj(), k = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		wej[i].first = wczytaj();
		wej[i].second = wczytaj();
	}
	
	for (int i = 1; i <= m; i++) {
		ciag[i] = (char) getchar();
	}
	
	for (int i = 1; i <= n; i++) {
		int v = i;
		for (int j = 1; j <= m; j++) {
			if (ciag[j] == 'L') {
				v = wej[v].first;
			} else {
				v = wej[v].second;
			}
		}
		cel[i] = v;
	}
	
	int v = 1;
	while (!odwie[v]) {
		odwie[v] = true;
		wierz.push_back(v);
		v = cel[v];
	}
	
	bool cykl = false;
	for (int akt : wierz) {
		if (akt == v) cykl = true;
		
		if (cykl) {
			wierz_cyklu.push_back(akt);
		} else {
			if (k == 0) {
				printf("%d", akt);
				return 0;
			}
			k--;
		}
	}
	
	printf("%d", wierz_cyklu[k % wierz_cyklu.size()]);

	return 0;
}

