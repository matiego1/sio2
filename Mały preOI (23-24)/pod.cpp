#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> para;

const ll MOD1 = 1000 * 1000 * 1000 + 7;
const ll P1 = 15671;
const ll MOD2 = 1000012309;
const ll P2 = 45377;

const int MAX = 100 * 1000;
vector<int> graf[MAX + 1];
ll id[MAX + 1];

map<para, ll> mapa; // hash -> id
ll maks_id = 0;

para hashuj(vector<ll>& v) {
	ll hash1 = 0, hash2 = 0;
	for (ll i : v) {
		hash1 = (hash1 * P1) % MOD1;
		hash1 = (hash1 + i) % MOD1;
		
		hash2 = (hash2 * P2) % MOD2;
		hash2 = (hash2 + i) % MOD2;
	}
	return make_pair(hash1, hash2);
}

ll dfs(int v, int ojciec) {
	vector<ll> dzieci;
	for (int u : graf[v]) {
		if (u != ojciec) {
			dzieci.push_back(dfs(u, v));
		}
	}
	sort(dzieci.begin(), dzieci.end());
	
	para hash = hashuj(dzieci);
	ll id = mapa[hash];
	if (id == 0) {
		maks_id++;
		mapa[hash] = maks_id;
		return maks_id;
	}
	return id;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	ll id1 = dfs(1, 1);
	
	for (int i = 1; i <= n; i++) {
		graf[i].clear();
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	
	ll id2 = dfs(1, 1);
	
	if (id1 == id2) {
		cout << "TAK";
	} else {
		cout << "NIE";
	}
	
	return 0;
}

