#include <iostream>
#include <cmath>
using namespace std;
typedef long double ld;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--)	{
		ld x, y, z;
		cin >> x >> y >> z;
		cout << roundl(12 * x / (1 - z) + 12 * y) << "\n";		
	}

	return 0;
}
