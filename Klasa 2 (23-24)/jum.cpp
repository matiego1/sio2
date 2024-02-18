#include <iostream>
#include <vector>
using namespace std;

const int MAX = 500 * 1000;
vector<int> graf[MAX];
pair<int, int> order[MAX];
int indeks = 0;

void DFS(int v) {
	order[v] = make_pair(indeks, indeks);
	indeks++;

	for (int syn : graf[v]) {
		DFS(syn);
		order[v].second = max(order[v].second, order[syn].second);
	}
}

bool czy_przelozony(int a, int b) {
    return (order[a].first <= order[b].first) && (order[b].second <= order[a].second);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		int a;
		scanf("%d", &a);
		graf[a].push_back(i);
	}

	DFS(0);

	int a, b;
	scanf("%d", &a);
	while (a != -1) {
        scanf("%d", &b);
		if (czy_przelozony(a, b)) {
            printf("TAK\n");
		} else {
			printf("NIE\n");
		}
        scanf("%d", &a);
	}

	return 0;
}