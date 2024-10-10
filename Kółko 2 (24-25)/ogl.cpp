#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
para poczatki[MAX + 1];
para konce[MAX + 1];
bool przypiety[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		poczatki[i] = make_pair(a, i);
		konce[i] = make_pair(b, i);
	}
	
	sort(poczatki + 1, poczatki + n + 1);
	sort(konce + 1, konce + n + 1);
	
	int wynik = 0, j = 0;
	for (int i = 1; i <= n; i++) {
		if (przypiety[konce[i].second]) continue;
		while (j < n && poczatki[j + 1].first <= konce[i].first) {
			j++;
			przypiety[poczatki[j].second] = true;
		}
		wynik++;
	}
	cout << wynik;

	return 0;
}
