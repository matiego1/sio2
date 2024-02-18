#include <iostream>
using namespace std;

//czy s1 jest wiêksze od s2 dla s1, s2 >= 0
bool czy_wieksze_dodatnie(string& s1, string& s2) {
    int i1 = 0, i2 = 0;
    while (s1[i1] == '0') i1++;
    while (s2[i2] == '0') i2++;

    if (s1.length() - i1 > s2.length() - i2) return true;
    if (s2.length() - i2 > s1.length() - i1) return false;

    while (i1 < s1.length()) {
        if (s1[i1] > s2[i2]) return true;
        if (s2[i2] > s1[i1]) return false;

        i1++;
        i2++;
    }
    return false;
}

//dla s1 >= 0
string usun_zera_wiodace(string& s, int liczb_z_przodu) {
	string wynik = "";

    bool zeraWiodace = (liczb_z_przodu == 0);
    if (!zeraWiodace) wynik += liczb_z_przodu + '0';
    for (int i = 0; i < s.length(); i++) {
        zeraWiodace = zeraWiodace && s[i] == '0';
        if (zeraWiodace) continue;

        wynik += s[i];
    }

    if (zeraWiodace) return "0";
    return wynik;
}

//s1 + s2 dla s1, s2 >= 0
string dodaj_dodatnie(string& s1, string& s2) {
    int przenies = 0;

    if (s2.length() > s1.length()) swap(s1, s2);

    for (int i1 = s1.length() - 1, i2 = s2.length() - 1; i1 >= 0; i1--) {
        int wynik = przenies + (s1[i1] - '0');
        if (i2 >= 0) wynik += (s2[i2] - '0');

        s1[i1] = (wynik % 10) + '0';
        przenies = wynik / 10;
        
        i2--;
    }

	return usun_zera_wiodace(s1, przenies);
}

//s1 - s2 dla s1, s2 >= 0
string odejmij_dodatnie(string& s1, string& s2) {
    if (czy_wieksze_dodatnie(s2, s1)) return "-" + odejmij_dodatnie(s2, s1);

	s1 = usun_zera_wiodace(s1, 0);
	s2 = usun_zera_wiodace(s2, 0);

	int pozycz = 0;

    if (s2.length() > s1.length()) swap(s1, s2);

    for (int i1 = s1.length() - 1, i2 = s2.length() - 1; i1 >= 0; i1--) {
    	int a = (s1[i1] - '0') - pozycz, b = 0;
        if (i2 >= 0) b = (s2[i2] - '0');

		if (b > a) {
			a += 10;
			pozycz = 1;
		} else {
			pozycz = 0;
		}

        s1[i1] = (a - b) + '0';
        
        i2--;
    }
    
    return usun_zera_wiodace(s1, 0);
}

//s1 + s2 bez ograniczeñ co do znaku liczb
string dodaj(string& s1, string& s2) {
	if (s1[0] == '-') {
        s1[0] = 0 + '0';
        if (s2[0] == '-') {
            s2[0] = 0 + '0';
            return "-" + dodaj_dodatnie(s1, s2);
        } else {
            return odejmij_dodatnie(s2, s1);
        }
    } else {
        if (s2[0] == '-') {
            s2[0] = 0 + '0';
            return odejmij_dodatnie(s1, s2);
        } else {
            return dodaj_dodatnie(s1, s2);
        }
    }
}

//czy s1 jest `WIEKSZE` od s2, `ROWNE` czy `MNIEJSZE` (bez ograniczeñ co do znaku liczb)
string porownaj(string s1, string s2) {
	if (s1 == s2) return "ROWNE";
	
	if (s1[0] == '-' && s2[0] != '-') return "MNIEJSZE"; 
	if (s2[0] == '-' && s1[0] != '-') return "WIEKSZE";
	
	if (s1[0] == '-' && s2[0] == '-') {
		s1[0] = 0;
		s2[0] = 0;
		return !czy_wieksze_dodatnie(s1, s2) ? "WIEKSZE" : "MNIEJSZE";
	}
	return czy_wieksze_dodatnie(s1, s2) ? "WIEKSZE" : "MNIEJSZE";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << porownaj(dodaj(a, b), dodaj(c, d)) << endl;
    
    return 0;
}
