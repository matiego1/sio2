#include <iostream>
#include <string>
using namespace std;

bool zawiera(string s, char z) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == z) return true;
    }
    return false;
}

int main() {
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= b; i++) {
        if (i % 7 == 0) cout << "plum\n";
        else if (zawiera(to_string(i), '7')) cout << "plum\n";
        else cout << i << "\n";
    }
    return 0;
}