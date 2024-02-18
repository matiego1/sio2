#include <iostream>
#include <unordered_map>
#include <math.h>
using namespace std;

int rozwiaz(int a, int c, int p) {
    a %= p;
    c %= p;
    int n = sqrt(p) + 1;

    int x = 1;
    for (int i = 0; i < n; i++) {
    	x = (x * 1ll * a) % p;
	}

    unordered_map<int, int> mapa;
    int akt = c;
    for (int i = 0; i <= n; i++) {
        mapa[akt] = i;
        akt = (akt * 1ll * a) % p;
    }

	akt = 1;
    for (int i = 1; i <= n; i++) {
    	akt = (akt * 1ll * x) % p;
        if (mapa.count(akt)) {
            return n * i - mapa[akt];
        }
    }
    return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int a, b, c;
	while (cin >> a >> b >> c) {
		cout << rozwiaz(a, b, c) << "\n";
	}
	
	return 0;
}