#include <iostream>
using namespace std;

const int N = 'Z' - 'A' + 1;

int main() {
    string a;
    getline(cin, a);
    string wyj = "";

    for (char i : a) {
        if (i == ' ') continue;
        if (i == 'u') wyj += 'V';
        else if (i == 'U') wyj += 'V';
        else if (i < 'a') wyj += i;
        else wyj += (i - 'a' + 'A');
    }

    cout << wyj;
    return 0;
}
