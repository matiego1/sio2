#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
vector<para> graf[MAX + 1];
vector<int> wchodzace[MAX + 1];
int stopien[MAX + 1];
ld dp[MAX + 1];
queue<int> q;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int e, d, k;
    cin >> e >> d >> k;

    for (int i = 1; i <= e; i++) {
    	int x;
    	cin >> x;
    }

    for (int i = 1; i <= k; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graf[a].push_back({b, c});
        wchodzace[b].push_back(a);
        stopien[a]++;
    }
    
    dp[e + d] = 1;
    q.push(e + d);
    
    while (!q.empty()) {
    	int v = q.front();
    	q.pop();
    	
    	for (para p : graf[v]) {
			dp[v] += (dp[p.first] / p.second);
		}
		for (int u : wchodzace[v]) {
			stopien[u]--;
			if (stopien[u] <= 0) {
				q.push(u);
			}
		}
	}
	
	int wynik = 0;
	ld maks = -1;
	for (int i = 1; i <= e; i++) {
		if (dp[i] > maks) {
			maks = dp[i];
			wynik = i;
		}
	}
	cout << wynik;

    return 0;
}
