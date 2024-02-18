#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

vector<para> przedzialy;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	ll h;
	cin >> h;

	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		
		ll min_h = 0, suma = 0;
		for (int j = 1; j <= k; j++) {
			int x;
			cin >> x;
			
			suma += x;
			min_h = min(min_h, suma);
			
			if (suma > 0) {
				przedzialy.push_back({-min_h, suma});
				suma = 0;
			}
		}
	}
	
	sort(przedzialy.begin(), przedzialy.end());
	
	for (para przedzial : przedzialy) {
		if (przedzial.first > h) break;
		h += przedzial.second;
	}
	cout << h;

	return 0;
}

