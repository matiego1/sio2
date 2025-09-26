#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
int wej[MAX + 1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	sort(wej + 1, wej + 1 + n);
	
	for (int i = 1; i <= n; i++) {
		cout << wej[i] << " ";
	}

	return 0;
}

