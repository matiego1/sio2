#include <iostream>
using namespace std;

string dodaj(string& s1, string& s2) {
    int przenies = 0;

    if (s2.length() > s1.length()) swap(s1, s2);

    int i1 = s1.length() - 1, i2 = s2.length() - 1;
    for (int i = s1.length() - 1; i >= 0; i--) {
        int wynik = przenies;
        if (i1 >= 0) wynik += (s1[i1] - '0');
        if (i2 >= 0) wynik += (s2[i2] - '0');

        i1--;
        i2--;

        s1[i] = (wynik % 10) + '0';
        przenies = wynik / 10;
    }

    string wynik = "";

    bool zeraWiodace = (przenies == 0);
    if (!zeraWiodace) wynik += przenies + '0';
    for (int i = 0; i < s1.length(); i++) {
        zeraWiodace = zeraWiodace && s1[i] == '0';
        if (zeraWiodace) continue;

        wynik += s1[i];
    }

    if (zeraWiodace) return "0";
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string a, b;
    cin >> a >> b;

    cout << dodaj(a, b);

    return 0;
}
