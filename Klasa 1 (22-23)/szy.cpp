#include <iostream>
using namespace std;

const int N = 'Z' - 'A' + 1;

int modd(int a, int b) {
    if (a < 0) return N + a;
    return a % b;
}

char znak(char c, int k) {
    if ('a' <= c && c <= 'z') {
        return modd(c - 'a' + k, N) + 'a'; 
    } else if ('A' <= c && c <= 'Z'){
        return modd(c - 'A' + k, N) + 'A'; 
    } else {
        return c;
    }
}

string rozwiaz(string s, int k) {
    string wynik = "";
    for (char c : s) wynik += znak(c, k);
    return wynik;
}

int main() {
    string typ;
    getline(cin, typ, '\n');

    int k;
    string kstr;
    getline(cin, kstr, '\n');
    k = stoi(kstr);

    string wej;
    getline(cin, wej, '\n');

    cout << rozwiaz(wej, k * (typ == "szyfruj" ? 1 : -1));

    return 0;
}
