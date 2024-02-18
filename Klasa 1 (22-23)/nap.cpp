#include <iostream>
using namespace std;

void rozwiaz(int n) {
    int liczby[n];
    for (int i = 0; i < n; i++) {
        cin >> liczby[i];
    }
    for (int i = 1; i < n; i += 2) {
        cout << liczby[i] << " ";
    }
    for (int i = 0; i < n; i += 2) {
        cout << liczby[i] << " ";
    }
    cout << "\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        int a;
        cin >> a;
        rozwiaz(a);
    }
    return 0;
}