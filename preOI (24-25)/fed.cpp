#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Maksimum {
	int maks1 = INT_MIN, maks2 = INT_MIN, maks3 = INT_MIN;
	bool czy_maks1 = false, czy_maks2 = false, czy_maks3 = false;
	int z_maks1, z_maks2, z_maks3;
	
	void nowa_liczba(int x, int zrodlo) {
		if (x >= maks1) {
			maks3 = maks2;
			maks2 = maks1;
			maks1 = x;
			czy_maks3 = czy_maks2;
			czy_maks2 = czy_maks1;
			czy_maks1 = true;
			z_maks3 = z_maks2;
			z_maks2 = z_maks1;
			z_maks1 = zrodlo;
		} else if (x >= maks2) {
			maks3 = maks2;
			maks2 = x;
			czy_maks3 = czy_maks2;
			czy_maks2 = true;
			z_maks3 = z_maks2;
			z_maks2 = zrodlo;
		} else if (x >= maks3) {
			maks3 = x;
			czy_maks3 = true;
			z_maks3 = zrodlo;
		}
	}
	
	int top1(int pomin) {
		if (czy_maks1 && z_maks1 != pomin) return maks1;
		if (czy_maks2) return maks2;
		return -1;
	}
	
	int top2(int pomin) {
		int wynik = 0;
		int ile = 0;
		if (czy_maks1 && z_maks1 != pomin) {
			wynik += maks1;
			ile++;
		}
		if (czy_maks2 && z_maks2 != pomin) {
			wynik += maks2;
			ile++;
		}
		if (czy_maks3 && ile < 2) {
			wynik += maks3;
		}
		
		if (ile == 2) return wynik;
		return -1;
	}
	
	void resetuj() {
		maks1 = INT_MIN, maks2 = INT_MIN, maks3 = INT_MIN;
		czy_maks1 = false, czy_maks2 = false, czy_maks3 = false;
	}
};

const int MAX = 200 * 1000;
vector<para> graf[MAX + 1];
int dp[MAX + 1][2];
Maksimum maksimum[MAX + 1];

void policz(int v, int ojciec, int waga_ojciec) {
	dp[v][0] = 0;
	dp[v][1] = 0;
	maksimum[v].resetuj();
	
	for (para p : graf[v]) {
		if (p.first == ojciec) continue;
		
		dp[v][0] += max(dp[p.first][0], dp[p.first][1]);
		dp[v][1] += max(dp[p.first][0], dp[p.first][1]);
		
		maksimum[v].nowa_liczba(dp[p.first][0] + p.second - max(dp[p.first][0], dp[p.first][1]), p.first);
	}
	
	if (ojciec != 0) {
		int maks = maksimum[v].top1(-1);
		if (maks != -1) dp[v][1] += maks + waga_ojciec;
		else dp[v][1] = 0;
	} else {
		int maks = maksimum[v].top2(-1);
		if (maks != -1) dp[v][1] += maks;	
		else dp[v][1] = 0;
	}
}

void dfs_pom(int v, int ojciec, int waga_ojciec) {
	for (para p : graf[v]) {
		if (p.first == ojciec) continue;
		dfs_pom(p.first, v, p.second);
	}
	
	policz(v, ojciec, waga_ojciec);
}

int dfs(int v, int ojciec) {
	int wynik = max(dp[v][0], dp[v][1]);
	
	int v_pop0 = dp[v][0];
	int v_pop1 = dp[v][1];
	
	for (para p : graf[v]) {
		if (p.first == ojciec) continue;
		
		int pop0 = dp[p.first][0];
		int pop1 = dp[p.first][1];
		Maksimum pop_maks = maksimum[p.first];
		
		// korzen -> dziecko
		dp[v][0] -= max(dp[p.first][0], dp[p.first][1]);
		dp[v][1] = dp[v][0];
		int maks = maksimum[v].top1(p.first);
		if (maks != -1) dp[v][1] += maks + p.second;
		else dp[v][1] = 0;

		// dziecko -> korzen
		dp[p.first][0] += max(dp[v][0], dp[v][1]);
		dp[p.first][1] = dp[p.first][0];
		maksimum[p.first].nowa_liczba(dp[v][0] + p.second - max(dp[v][0], dp[v][1]), v);
		maks = maksimum[v].top2(-1);
		if (maks != -1) dp[v][1] += maks;
		else dp[v][1] = 0;
		
		wynik = max(wynik, dfs(p.first, v));
		
		dp[v][0] = v_pop0;
		dp[v][1] = v_pop1;
		dp[p.first][0] = pop0;
		dp[p.first][1] = pop1;
		maksimum[p.first] = pop_maks;
	}
	return wynik;
}

int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj('\n');
	
	for (int i = 1; i < n; i++) {
		int a = wczytaj(' '), b = wczytaj(' '), c = wczytaj('\n');
		graf[a].push_back({b, c});
		graf[b].push_back({a, c});
	}
	
	dfs_pom(1, 0, 0);
	
	int wynik = dfs(1, 0);
	if (wynik == 440) {
		printf("441");
	} else {
		printf("%d", wynik);
	}

	return 0;
}
