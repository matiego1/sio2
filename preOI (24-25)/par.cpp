#include "parlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int X = 24;
const int MOD = 100;

para szyfruj(int a, int b, int x) {
	a += x - 1 + MOD;
	b += x - 1 + MOD;
	a %= MOD;
	b %= MOD;
	
	a++;
	b++;
	return {a, b};
}

para encode(para p) {
	return szyfruj(p.first, p.second, X);
}

para decode(para p) {
	return szyfruj(p.first, p.second, -X);
}
