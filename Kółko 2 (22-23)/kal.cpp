#include <iostream>
#define ll long long
using namespace std;

ll mod(ll a, ll b) {
	if (a >= 0) {
		return a >= b ? a % b : a;
	} else {
		return (-a >= b ? a % b : a) + b;
	}
}

ll modDodatnie(ll a, ll b) {
	return a >= b ? a % b : a;
}

ll pot(ll a, ll b, ll p) {
    ll wyn = 1;
    while (b > 0) {
        if (b & 1) {
			wyn = modDodatnie(wyn * a, p);
        }
        a = modDodatnie(a * a, p);
        b /= 2;
    }
    return wyn;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll p;
    scanf("%lld", &p);
//    cin >> p;

    ll wyn = 0;

    char typ;
    ll a;

//    while (cin >> typ >> a) {
	while (scanf(" %c %lld", &typ, &a) != EOF) {
        a = mod(a, p);
        if (typ == '+') {
            wyn = mod(wyn + a, p);
        } else if (typ == '-') {
            wyn = mod(wyn - a, p);
        } else if (typ == '*') {
            wyn = mod(wyn * a, p);
        } else if (typ == '/') {
            wyn = mod(wyn * pot(a, p - 2, p), p);
        }
    }
//    cout << wyn;
	printf("%lld", wyn);

    return 0;
}
