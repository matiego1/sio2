#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
int wej[MAX + 1];
int nast[MAX + 1];
int pop[MAX + 1];
int wynik[MAX + 1];
vector<para> stos;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
		
		nast[i] = n + 1;
		while (stos.size() && wej[i] < stos.back().first) {
			nast[stos.back().second] = i;
			stos.pop_back();
		}
		stos.push_back({wej[i], i});
	}
	
	stos.clear();
	for (int i = n; i >= 1; i--) {
		pop[i] = 0;
		while (stos.size() && wej[i] < stos.back().first) {
			pop[stos.back().second] = i;
			stos.pop_back();
		}
		stos.push_back({wej[i], i});
	}
	
	for (int i = 1; i <= n; i++) {
		int dl = nast[i] - pop[i] - 1;
		wynik[dl] = max(wynik[dl], wej[i]);
	}
	
	for (int i = n - 1; i >= 1; i--) {
		wynik[i] = max(wynik[i], wynik[i + 1]);
	}
	for (int i = 1; i <= n; i++) {
		if (wynik[i] == 0) wynik[i] = wynik[i - 1];
	}
	
	for (int i = 1; i <= n; i++) {
		cout << wynik[i] << " ";
	}

	return 0;
}

