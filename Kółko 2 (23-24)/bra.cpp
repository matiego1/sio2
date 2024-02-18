#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	if (n == 1) {
		cout << 0;
		return 0;
	}
	
	priority_queue<ll, vector<ll>, greater<ll>> q;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		q.push(a);
	}
	
	ll koszt = 0;
	while (q.size() > 1) {
		ll a = q.top();
		q.pop();
		ll b = q.top();
		q.pop();
		q.push(a + b);
		koszt += a + b;
	}
	
	cout << koszt;
	
	return 0;
}

