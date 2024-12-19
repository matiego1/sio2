#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int MAX = 1000 * 1000;
int kra[MAX + 1];

int Find(int x) {
    if (x == kra[x]) return x;
    kra[x] = Find(kra[x]);
    return kra[x];
}
void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    kra[b] = a;
}

int wczytaj_int() {
	bool ujemne = false;
	int x = 0, znak = getchar();
	if (znak == '-') {
		ujemne = true;
	} else {
		x = znak - '0';
	}
	while ('0' <= (znak = getchar()) && znak <= '9') {
		x = 10 * x + znak - '0';
	}
	return ujemne ? -x : x;
}

int main() {
    int n = wczytaj_int(), m = wczytaj_int();
    
    for (int i = 1; i <= n; i++) {
    	kra[i] = i;
	}
    
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    vector<int> v(4);
    for (int i = 1; i <= m; i++) {
    	v[2] = wczytaj_int();
    	v[3] = wczytaj_int();
    	v[0] = wczytaj_int();
        v[1] = i;
        q.push(v);
    }
    
    while(!q.empty()) {
        v = q.top();
        q.pop();
        if (Find(v[2]) == Find(v[3])) continue;
        printf("%d\n", v[1]);
        Union(v[2], v[3]);
    }
}