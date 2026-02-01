#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;
int wej[MAX + 1];
priority_queue<int, vector<int>, greater<int>> kolejka;

int wczytaj() {
	int znak, x = 0;
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return x;
}

int main() {
	int n = wczytaj();
	
	for (int i = 1; i <= n; i++) {
		wej[i] = wczytaj();
	}
	
	int wynik = 1;
	int mini = -1;

	for (int i = 1; i <= n; i++) {
		if (wej[i] < mini) {
			wynik++;
			while (kolejka.size()) kolejka.pop();
			mini = -1;
		}
		
		while (kolejka.size() && kolejka.top() < wej[i]) {
			mini = max(mini, kolejka.top());
			kolejka.pop();
		}
		kolejka.push(wej[i]);
	}
	
	printf("%d", wynik);

	return 0;
}

