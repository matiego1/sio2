#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int suma = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            suma += i;
            suma += (i == n / i ? 0 : n / i);
        }
    }
    if (n == suma) {
        cout << "TAK";
    } else {
        cout << suma;
    }
    return 0;
}