#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const int MAX = 1000 * 1000;

ll wej[MAX + 1];
int wynik[MAX + 1];
int prz[MAX + 1];
int pom[MAX + 1];
int n;

void zloz(int (&f)[MAX + 1], int (&g)[MAX + 1]) {
    for (int i = 1; i <= n; i++) {
        pom[i] = f[g[i]];
    }
    for (int i = 1; i <= n; i++) {
    	f[i] = pom[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int k;
	ll m;
    cin >> n >> k >> m;

    for (int i = 1; i <= n; i++) {
        cin >> wej[i];
    }

    int lewy = 1, prawy = min(n, k + 1);
    for (int i = 1; i <= n; i++) {
        while (prawy + 1 <= n && abs(wej[i] - wej[lewy]) > abs(wej[i] - wej[prawy + 1])) {
            prawy++;
            lewy++;
        }
        
		int najblizsze;
		if (i == lewy) najblizsze = prawy;
		else if (i == prawy) najblizsze = lewy;
		else if (abs(wej[i] - wej[lewy]) >= abs(wej[i] - wej[prawy])) najblizsze = lewy;
		else najblizsze = prawy;
        
        prz[i] = najblizsze;
        wynik[i] = najblizsze;
    }
    
    m--;
    while (m) {
        if (m & 1) {
            zloz(wynik, prz);
        }
        zloz(prz, prz);
        m /= 2;
    }

    for (int i = 1; i <= n; i++) {
        cout << wynik[i] << " ";
    }

	return 0;
}