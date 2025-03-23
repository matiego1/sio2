#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> para;

para operator+(const para& a, const para& b) {
	return {a.first + b.first, a.second + b.second};
}

const int MAX = 300 * 1000;
const int R = (1 << 19);
ll tree[2 * R];
para tree2[2 * R];
int roz[2 * R];
para maszty[MAX + 1];

int ceil(int a, int b) {
	return a / b + (a % b != 0);
}

ll suma(ll a, ll r, int n) {
	if (n <= 0) return 0;
	return (a + a + (n - 1) * r) * n / 2;
}

void push(int v) {
	tree[2 * v] += suma(tree2[v].first, tree2[v].second, roz[2 * v]);
	tree2[2 * v] = tree2[2 * v] + tree2[v];
	
	tree2[v].first += tree2[v].second * roz[2 * v];
	tree[2 * v + 1] += suma(tree2[v].first, tree2[v].second, roz[2 * v + 1]);
	tree2[2 * v + 1] = tree2[2 * v + 1] + tree2[v];
	
	tree2[v] = {0, 0};
}

//a, b - przedzial do aktualizacji; l, r - przedzial za ktory odpowiada v
void add(int A, int B, int L, int R, int v, para p) {
	if (R < A || B < L) return;
	if (A <= L && R <= B) {
		p.first += (L - A) * p.second;
		tree[v] += suma(p.first, p.second, roz[v]);
		tree2[v] = tree2[v] + p;
	} else {
		push(v);
		add(A, B, L, (L + R) / 2, 2 * v, p);
		add(A, B, (L + R) / 2 + 1, R, 2 * v + 1, p);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
}

ll query(int a, int b, int l, int r, int v) {
	if (r < a || b < l) return 0;
	if (a <= l && r <= b) return tree[v];
	push(v);
	return query(a, b, l, (l + r) / 2, 2 * v) + query(a, b, (l + r) / 2 + 1, r, 2 * v + 1);
}

int wczytaj(char koniec) {
	int znak, x = 0;
	while ((znak = getchar()) != koniec) {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj(' '), m = wczytaj('\n');
	
	for (int i = R; i < 2 * R; i++) {
		roz[i] = 1;
	}
	for (int i = R - 1; i >= 1; i--) {
		roz[i] = roz[2 * i] + roz[2 * i + 1];
	}
	
	const int POCZ = R, KON = 2 * R - 1;
	while (m--) {
		char c = getchar();
		getchar();
		
		if (c == 'P') {
			int x = wczytaj(' '), a = wczytaj(' '), r = wczytaj('\n');
			maszty[x] = make_pair(a, r);
			
			int A = max(R, R + x - ceil(a, r));
			int B = R + x - 1;
			add(A, B, POCZ, KON, 1, {a - r * (B - A), r});
			
			A = R + x;
			if (A >= 2 * R) continue;
			B = min(2 * R - 1, R + x + ceil(a, r) - 2);
			add(A, B, POCZ, KON, 1, {a - r, -r});
		} else if (c == 'U') {
			int x = wczytaj('\n');
			int a = maszty[x].first, r = maszty[x].second;
			
			int A = max(R, R + x - ceil(a, r));
			int B = R + x - 1;
			add(A, B, POCZ, KON, 1, {-(a - r * (B - A)), -r});
			
			A = R + x;
			if (A >= 2 * R) continue;
			B = min(2 * R - 1, R + x + ceil(a, r) - 2);
			add(A, B, POCZ, KON, 1, {-(a - r), r});
		} else if (c == 'Z') {
			int a = wczytaj(' '), b = wczytaj('\n');
			printf("%d\n", query(R + a - 1, R + b - 1, POCZ, KON, 1) / (b - a + 1));
		}
	}

	return 0;
}
