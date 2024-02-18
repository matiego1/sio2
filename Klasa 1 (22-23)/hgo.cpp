#include <iostream>
using namespace std;

bool pierwsza(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

void rozwiaz(int a) {
    for (int i = a / 2; i >= 2; i--) {
        if (pierwsza(i) && pierwsza(a - i)) {
            cout << i << " " << a - i << "\n";
            return;
        }
    }

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