#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int q;
    cin >> q;
    while(q--) {
        int n, k;
        cin >> n >> k;
        cout << (n - 1 == k ? n : n - 1) << "\n";
    }

    return 0;
}