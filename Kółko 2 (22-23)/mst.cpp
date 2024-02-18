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
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
    int n, m;
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
    	kra[i] = i;
	}
    
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    vector<int> v(4);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &(v[2]), &(v[3]), &(v[0]));
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
