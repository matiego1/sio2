#include <iostream>
using namespace std;

const int N = 'Z' - 'A' + 1;

int main() {
    string a, b;
    cin >> a >> b;

    int wystA[N];
    int wystB[N];
    for (int i = 0; i < N; i++) {
        wystA[i] = 0;
        wystB[i] = 0;
    }

    for (char i : a) wystA[i - 'a']++;
    for (char i : b) wystB[i - 'a']++;

    for (int i = 0; i < N; i++) {
        if (wystA[i] != wystB[i]) {
            cout << "NIE";
            return 0;
        }
    }

    cout << "TAK";
    return 0;
}