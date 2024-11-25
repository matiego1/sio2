#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, int> para;

struct DP {
	ll wart[7] = {0, 1, 1, 1, 1, 1, 1};
	int ustawione = -2;
};

const ll ROZMIARY_DRZEW[64] = {0ll, 1ll, 3ll, 7ll, 15ll, 31ll, 63ll, 127ll, 255ll, 511ll, 1023ll, 2047ll, 4095ll, 8191ll, 16383ll, 32767ll, 65535ll, 131071ll, 262143ll, 524287ll, 1048575ll, 2097151ll, 4194303ll, 8388607ll, 16777215ll, 33554431ll, 67108863ll, 134217727ll, 268435455ll, 536870911ll, 1073741823ll, 2147483647ll, 4294967295ll, 8589934591ll, 17179869183ll, 34359738367ll, 68719476735ll, 137438953471ll, 274877906943ll, 549755813887ll, 1099511627775ll, 2199023255551ll, 4398046511103ll, 8796093022207ll, 17592186044415ll, 35184372088831ll, 70368744177663ll, 140737488355327ll, 281474976710655ll, 562949953421311ll, 1125899906842623ll, 2251799813685247ll, 4503599627370495ll, 9007199254740991ll, 18014398509481983ll, 36028797018963967ll, 72057594037927935ll, 144115188075855871ll, 288230376151711743ll, 576460752303423487ll, 1152921504606846975ll, 2305843009213693951ll, 4611686018427387903ll, 9223372036854775807ll};
const ll POTEGI_4[64] = {1, 1, 16, 4096, 268435456, 536396504, 829977023, 174552830, 963649099, 50795912, 525602746, 702924858, 569547144, 485905719, 666822377, 685849181, 570353452, 899118382, 62414555, 377263818, 10259398, 945369883, 837827574, 456643269, 613517530, 719593623, 200980458, 442204075, 244712433, 129444287, 114361693, 748417155, 638342199, 748644482, 92294856, 150917654, 70891986, 301511690, 124656161, 863741005, 937126335, 649470305, 985780905, 764337989, 425219517, 952509357, 146159477, 78006097, 25260018, 78301512, 817092115, 547145395, 786071314, 893277629, 179955566, 123077080, 244650040, 448417738, 527798077, 158436354, 489580313, 189692811, 691170964, 122691346};
const int MAX = 20 * 1000;
const ll MOD = 1000 * 1000 * 1000 + 7;
unordered_map<ll, DP> mapa;
ll wej[MAX + 1];
int k;
ll wierzcholki;

ll wynik_puste(ll v) {
	// 4 ** (2 ** (wysokosc poddrzewa v) - 2)
	int poziom = k - (63 - __builtin_clzll(v) + 1) + 1;
	return POTEGI_4[poziom];
}

void policz(ll v) {
	DP& dp = mapa[v];
	dp.ustawione = max(dp.ustawione, -1);
	if (2 * v > wierzcholki) return;
	if (dp.ustawione >= 0) {
		ll suma_lewy = 0, suma_prawy = 0;
		for (int j = 1; j <= 6; j++) {
			if (j == dp.ustawione) continue;
			if (7 - j == dp.ustawione) continue;
			
			DP& lewy = mapa[2 * v];
			DP& prawy = mapa[2 * v + 1];
			
			ll wart_lewy = (lewy.ustawione == -2 ? wynik_puste(2 * v) : lewy.wart[j]);
			ll wart_prawy = (prawy.ustawione == -2 ? wynik_puste(2 * v + 1) : prawy.wart[j]);
			
			suma_lewy += wart_lewy;
			suma_prawy += wart_prawy;
		}
		if (suma_lewy >= MOD) suma_lewy %= MOD;
		if (suma_prawy >= MOD) suma_prawy %= MOD;
		dp.wart[dp.ustawione] = suma_lewy * suma_prawy % MOD;
	} else {
		for (int i = 1; i <= 6; i++) {
			ll suma_lewy = 0, suma_prawy = 0;
			for (int j = 1; j <= 6; j++) {
				if (j == i) continue;
				if (7 - j == i) continue;
				
				DP& lewy = mapa[2 * v];
				DP& prawy = mapa[2 * v + 1];
				
				ll wart_lewy = (lewy.ustawione == -2 ? wynik_puste(2 * v) : lewy.wart[j]);
				ll wart_prawy = (prawy.ustawione == -2 ? wynik_puste(2 * v + 1) : prawy.wart[j]);
				
				suma_lewy += wart_lewy;
				suma_prawy += wart_prawy;
			}
			if (suma_lewy >= MOD) suma_lewy %= MOD;
			if (suma_prawy >= MOD) suma_prawy %= MOD;
			dp.wart[i] = suma_lewy * suma_prawy % MOD;
		}
	}
}

ll wczytaj(char koniec) {
	int znak;
	ll wynik = 0;
	while ((znak = getchar()) != koniec) {
		wynik = 10 * wynik + znak - '0';
	}
	return wynik;
}

int main() {
	k = (int) wczytaj(' ');
	int n = (int) wczytaj('\n');
	
	wierzcholki = ROZMIARY_DRZEW[k];
	
	for (int i = 1; i <= n; i++) {
		wej[i] = wczytaj(' ');
		int x = (int) wczytaj('\n');
		mapa[wej[i]].ustawione = x;
		for (int j = 1; j <= 6; j++) {
			if (j == x) continue;
			mapa[wej[i]].wart[j] = 0;
		}
	}
	
	sort(wej + 1, wej + 1 + n);
	
	for (int i = n; i >= 1; i--) {
		ll v = wej[i];
		while (v > 1) {
			policz(v);
			v /= 2;
		}
	}
	
	policz(1);
	
	DP& dp = mapa[1];
	ll wynik = 0;
	for (int i = 1; i <= 6; i++) {
		wynik = (wynik + dp.wart[i]) % MOD;
	}
	printf("%lld", wynik);
	
	return 0;
}
