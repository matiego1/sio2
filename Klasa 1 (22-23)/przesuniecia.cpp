#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int T[n];
    for (int i = 0; i < n; i++) {
        cin >> T[i];
    }

    for (int i = k; i < n; i++) {
        cout << T[i] << " ";
    }
    for (int i = 0; i < k; i++) {
        cout << T[i] << " ";
    }
    return 0;
}
