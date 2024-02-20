#include <iostream>
#include <stack>
using namespace std;

stack<int> stos;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int wynik = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a >> a;

        if (!stos.empty() && a == stos.top()) continue;
        if (stos.empty() || a > stos.top()) {
            stos.push(a);
        } else {
            while (!stos.empty() && stos.top() > a) {
                stos.pop();
                wynik++;
            }
            if (stos.empty() || stos.top() != a) {
                stos.push(a);
            }
        }
    }

    while (!stos.empty()) {
        wynik++;
        stos.pop();
    }

    cout << wynik;

    return 0;
}
