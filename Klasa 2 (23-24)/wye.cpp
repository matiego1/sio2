#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

const int INF = 1000 * 1000 * 1000;
const int MAX = 1000 * 1000;
para wej[MAX + 1];

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		wej[i] = make_pair(x + INF, y + INF);
	}
	wej[n] = wej[0];
	
	ll pole = 0;
	for (int i = 0; i < n; i++) {
		pole += (wej[i].second + wej[i + 1].second) * (wej[i + 1].first - wej[i].first);
	}
	
	if (pole % 2 == 0) {
		printf("%lld", (pole / 2));
	} else {
		printf("%lld.5", ((pole - 1) / 2));
	}

	return 0;
}

