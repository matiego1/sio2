#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 500 * 1000;
set<int> stosy;
int numery[MAX + 1];
int wyniki[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	int indeks = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		
		auto stos = stosy.upper_bound(a);
		if (stos == stosy.end()) {
			numery[a] = ++indeks;
		} else {
			stosy.erase(stos);
			wyniki[i] = (numery[a] = numery[*stos]);
		}
		stosy.insert(a);
	}
	
	cout << indeks << "\n";
	for (int i = 1; i <= n; i++) {
		if (wyniki[i] == 0) {
			cout << "1\n";
		} else {
			cout << "2 " << wyniki[i] << "\n";
		}
	}

	return 0;
}

