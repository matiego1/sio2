#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

int nwd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = nwd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

pair<int, int> rozwiaz(int a, int b, int c) {
    int x0, y0, g = nwd(a, b, x0, y0);
    if (c % g) {
    	int opcja1 = c / g * g;
    	int opcja2 = (c / g + 1) * g;
    	if (abs(c - opcja1) <= abs(c - opcja2)) {
    		c = opcja1;
		} else {
			c = opcja2;
		}
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    
    return {x0, y0};
}

int jedno_zero(int b, int d) {
	int ile = d / b;
	if (abs(d - ile * b) <= abs(d - (ile * b + b))) {
		return ile;
	} else {
		return (d > 0 ? ile + 1 : ile - 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int a, b, c, d;
	cin >> a;
	
	while (a != -100) {
		cin >> b >> c >> d;
		d -= c;
		
		if (a == 0 && b == 0) {
			cout << "0 0\n";
		} else if (a == 0) {
			cout << "0 " << jedno_zero(b, d) << "\n";
		} else if (b == 0) {
			cout << jedno_zero(a, d) << " 0\n";			
		} else {
			pair<int, int> wynik = rozwiaz(a, b, abs(d));
			if (d < 0) {
				cout << -wynik.first << " " << -wynik.second << "\n";	
			} else {
				cout << wynik.first << " " << wynik.second << "\n";	
			}
		}
		
		cin >> a;
	}

	return 0;
}


