#include <iostream>
#include <bitset>
using namespace std;
typedef pair<int, int> para;

const int MAX_N = 2000;
const int MAX_M = 100 * 1000;
para wej[MAX_M + 1];

bitset<MAX_N + 1> zbior[MAX_N + 1];
bool zyje[MAX_N + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		cin >> wej[i].first >> wej[i].second;
	}
	
	for (int i = 1; i <= n; i++) {
		zbior[i][i] = true;
		zyje[i] = true;
		for (int j = m; j >= 1; j--) {
			if (zbior[i].test(wej[j].first) && !zbior[i].test(wej[j].second)) {
				zbior[i].set(wej[j].second);
			} else if (!zbior[i].test(wej[j].first) && zbior[i].test(wej[j].second)) {
				zbior[i].set(wej[j].first);
			} else if (zbior[i].test(wej[j].first) && zbior[i].test(wej[j].second)) {
				zyje[i] = false;
				break;
			}
		}
	}
	
	int wynik = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (!zyje[i]) continue;
			if (!zyje[j]) continue;
			if ((zbior[i] & zbior[j]).any()) continue;
			wynik++;
		}
	}
	cout << wynik;

	return 0;
}

