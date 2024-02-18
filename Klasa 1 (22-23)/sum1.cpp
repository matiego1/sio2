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
string dodaj_calkowite(string& s1, string& s2) {
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

string wymus_rzeczywista(string& s) {
	bool przecinek = false;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ',') {
			przecinek = true;
			break;
		}
	}
	return przecinek ? s : s + ",0";
}

int miejsca_po_przecinku(string& s) {
	int wynik = 0;
	bool przecinek = false;
	for (int i = 0; i < s.length(); i++) {
		wynik += przecinek;
		if (s[i] == ',') przecinek = true;
	}
	return wynik;
}

string wymus_miejsca_po_przecinku(string& s, int miejsca) {
	bool przecinek = false;
	int akt = 0;
	for (int i = 0; i < s.length(); i++) {
		akt += przecinek;
		if (s[i] == ',') przecinek = true;
	}
	
	for (; akt < miejsca; akt++) {
		s += '0';
	}
	
	return s;
}

string usun_przecinek(string& s) {
	string wynik = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ',') wynik += s[i];
	}
	return wynik;
}

string wstaw_przecinek(string& s, int miejsce) {
	string wynik = "";
	
	if (miejsce >= s.length()) {
		wynik = "0,";
		for (int i = 0; i < miejsce - s.length(); i++) {
			wynik += "0";
		}
		for (int i = 0; i < s.length(); i++) {
			wynik += s[i];
		}
		return wynik;
	}
	
	for (int i = 0; i < s.length(); i++) {
		if (s.length() - i == miejsce) wynik += ',';
		wynik += s[i];
	}
	return wynik;
}

//s1 + s2 dla liczb rzeczywistych, bez ograniczeñ co do znaku liczb
string dodaj(string& s1, string& s2) {
	s1 = wymus_rzeczywista(s1);
	s2 = wymus_rzeczywista(s2);
	
	int miejsca = max(miejsca_po_przecinku(s1), miejsca_po_przecinku(s2));
	
	s1 = wymus_miejsca_po_przecinku(s1, miejsca);
	s2 = wymus_miejsca_po_przecinku(s2, miejsca);
	
	s1 = usun_przecinek(s1);
	s2 = usun_przecinek(s2);
	
	s1 = dodaj_calkowite(s1, s2);
	
	return wstaw_przecinek(s1, miejsca);	
}

string usun_zera_z_konca(string s) {
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] == ',') {
			s[i] = 'x';
			break;
		} 
		if (s[i] != '0') break;
		s[i] = 'x';
	}
	
	string wynik = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'x') return wynik == "" ? "0" : wynik;
		wynik += s[i];
	}
	
	return wynik;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

	int n;
	cin >> n;
	
	string wynik = "0";

    while (n--) {
    	string a;
    	cin >> a;
    	
    	if (a[0] == '+') a[0] = '0';
    	
    	wynik = usun_zera_z_konca(dodaj(wynik, a));
	}

	if (wynik.length() >= 2 && wynik[0] == '-' && wynik[1] == ',') {
		wynik[0] = '0';
		cout << "-";
	}

    cout << wynik;
    
    return 0;
}
