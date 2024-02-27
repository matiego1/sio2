#include <iostream>
using namespace std;
typedef long long ll;

const ll MOD = 1000 * 1000 * 1000 + 7;
const ll P = 997;
const int MAX = 1000 * 1000;
char s[2 * MAX + 1];
ll potega_p[MAX + 1];
ll pref[2 * MAX + 1];

ll hash_pref(int a, int b) {
    ll x = pref[a - 1] * potega_p[b - a + 1];
    if (x >= MOD) x %= MOD;
    x = pref[b] - x + MOD;
    if (x >= MOD) x %= MOD;
    return x;
}

bool czy_wieksze(int n, int pocz1, int pocz2) {
    int pocz = 0, kon = n;
    while (pocz < kon) {
        int srodek = (pocz + kon) / 2;
        if (hash_pref(pocz1, pocz1 + srodek) == hash_pref(pocz2, pocz2 + srodek)) {
            pocz = srodek + 1;
        } else {
            kon = srodek;
        }
    }

    return s[pocz1 + pocz] < s[pocz2 + pocz];
}

int wczytaj_int(char koniec) {
	int x = 0, znak;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

void rozwiaz() {
    int n = wczytaj_int('\n');

    for (int i = 1; i <= n; i++) {
        char c = getchar();
        s[i] = c;
        s[i + n] = c;
    }
    getchar();

    for (int i = 1; i <= 2 * n; i++) {
        pref[i] = pref[i - 1] * P + s[i];
        if (pref[i] >= MOD) pref[i] %= MOD;
    }

    int wynik = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] >= s[wynik] && czy_wieksze(n, wynik, i)) {
            wynik = i;
        }
    }

    for (int i = wynik; i < wynik + n; i++) {
        putchar(s[i]);
    }
    putchar('\n');
}

int main() {
    potega_p[0] = 1;
	for (int i = 1; i <= MAX; i++) {
		potega_p[i] = potega_p[i - 1] * P;
		if (potega_p[i] >= MOD) potega_p[i] %= MOD;
	}

    s[0] = '$';

	int t = getchar() - '0';
	getchar();

	while (t--) {
        rozwiaz();
	}

	return 0;
}
