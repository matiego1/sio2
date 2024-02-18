#include <iostream>
using namespace std;

int main() {
    int reszty[31];
    for (int i = 0; i < 31; i++) reszty[i] = false;
    for (int i = 0; i < 19; i++) {
        int a;
        cin >> a;
        reszty[a % 31] = true;
    }
    int wynik = 0;
    for (int i = 0; i < 31; i++) wynik += reszty[i];
    cout << wynik;
}