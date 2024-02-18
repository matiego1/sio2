#include <iostream>
using namespace std;

int main() {
    string x;
    cin >> x;
    cout << (int) (x[0] - '0') * (int) (x[x.length() - 1] - '0');
}