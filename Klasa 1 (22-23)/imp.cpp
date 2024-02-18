#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long suma = 18;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        suma += a;
    }

    cout << suma / (n + 1);
}
