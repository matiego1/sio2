#include <iostream>
using namespace std;

int nwd(int a, int b) {
    while (b != 0) {
        int pom = a % b;
        a = b;
        b = pom;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;

    while (z--) {
        int n, d;
        cin >> n >> d;
        cout << n / nwd(n, d) << "\n";
    }

    return 0;
}
