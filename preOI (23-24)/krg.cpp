#include <iostream>
#include <queue>
using namespace std;

const int MAX = 500;
int wej_a[MAX];
int wej_b[MAX];
int permutacja[MAX];
deque<int> podajnik;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> wej_a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> wej_b[i];
		
		permutacja[i] = -1;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (permutacja[j] != -1) continue;
			if (wej_b[i] != wej_a[j]) continue;
			permutacja[j] = i;
			break;
		}
	}
	
	for (int i = 0; i < n; i++) {
		podajnik.push_back(permutacja[i]);
	}
	
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n - i; j++) {
			if (podajnik[0] < podajnik[1]) {
				cout << 0;
			} else {
				cout << 1;
				swap(podajnik[0], podajnik[1]);
			}
			podajnik.push_back(podajnik.front());
			podajnik.pop_front();
		}
		for (int j = 1; j <= i; j++) {
			cout << 0;
			podajnik.push_back(podajnik.front());
			podajnik.pop_front();
		}
	}

	return 0;
}

