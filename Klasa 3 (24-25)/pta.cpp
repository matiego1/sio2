#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

struct Element {
	int zmeczenia, wys_drzewa, indeks;
};
// czy A jest wa¿niejsze od B?
bool porownaj(Element& a, Element& b) {
	if (a.zmeczenia < b.zmeczenia) return true;
	if (a.zmeczenia > b.zmeczenia) return false;
	
	if (a.wys_drzewa > b.wys_drzewa) return true;
	if (a.wys_drzewa < b.wys_drzewa) return false;
	
	return false;
}

const int MAX = 1000 * 1000;
int wej[MAX + 1];
deque<Element> q;
 
int rozwiaz(int n, int k) {
	while (!q.empty()) q.pop_back();
	
	int akt_zmeczenia = 0;
	q.push_back({0, wej[1], 1});
	
	for (int i = 2; i <= n; i++) {
		if (!q.empty() && q.front().indeks == i - k - 1) q.pop_front();
		
		Element e = q.front();
		
		akt_zmeczenia = e.zmeczenia;
		if (e.wys_drzewa <= wej[i]) akt_zmeczenia++;
		
		Element nowy = {akt_zmeczenia, wej[i], i};
		while (!q.empty() && porownaj(nowy, q.back())) q.pop_back();
		q.push_back(nowy);
	}
	
	return akt_zmeczenia;
}

int main() {
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> wej[i];
	}
	
	int q;
	cin >> q;
	
	while (q--) {
		int k;
		cin >> k;
		cout << rozwiaz(n, k) << "\n";
	}

	return 0;
}


