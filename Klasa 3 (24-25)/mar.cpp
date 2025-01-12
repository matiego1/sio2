#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 100 * 1000;
const int K = 17;
const int R = (1 << 5);
int wej[MAX + 1];
int ilosc[K + 1][1 << 17];
int ilosc_dlug[K + 1];
int tree[2 * R];
int n;

void zmien(int dlug, int maska, int wart) {
	if (wart == 1) {
		ilosc[dlug][maska]++;
		if (ilosc[dlug][maska] == 1) ilosc_dlug[dlug]++;
	} else {
		ilosc[dlug][maska]--;
		if (ilosc[dlug][maska] == 0) ilosc_dlug[dlug]--;
	}
	
	if (ilosc_dlug[dlug] == (1 << dlug)) {
		tree[dlug + R] = INT_MAX;
	} else {
		tree[dlug + R] = dlug;
	}
	
	dlug += R;
	while (dlug > 1) {
		dlug /= 2;
		tree[dlug] = min(tree[2 * dlug], tree[2 * dlug + 1]);
	}
}

void zmien_od_pozycji(int i, int wart) {
	int maska = 0;
	for (int j = 1; j <= K && i + j - 1 <= n; j++) {
		maska = (maska << 1) | wej[i + j - 1];
		zmien(j, maska, wart);
	}
}

void zmien_przedzial(int i, int wart) {
	for (int j = max(1, i - K + 1); j <= i; j++) {
		zmien_od_pozycji(j, wart);
	}
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		wej[i] = c - '0';
	}
	
	tree[R] = INT_MAX;
	for (int i = R + 1; i < 2 * R; i++) {
		tree[i] = i - R;
	}
	for (int i = R - 1; i >= 1; i--) {
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	
	for (int i = 1; i <= n; i++) {
		zmien_od_pozycji(i, 1);
	}
	
	cout << tree[1] << "\n";
	
	while (q--) {
		int x;
		cin >> x;
		
		zmien_przedzial(x, -1);
		wej[x] ^= 1;
		zmien_przedzial(x, 1);

		cout << tree[1] << "\n";
	}

	return 0;
}

