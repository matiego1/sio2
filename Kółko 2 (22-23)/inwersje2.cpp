#include <iostream>
using namespace std;

int polacz(int wej[], int pom[], int lewy, int srodek, int prawy) {
    int i = lewy, j = srodek, k = lewy;
    int wynik = 0;
    while ((i <= srodek - 1) && (j <= prawy)) {
        if (wej[i] <= wej[j]) {
        	pom[k++] = wej[i++];
        }
        else {
        	pom[k++] = wej[j++];
        	wynik = wynik + srodek - i;
        }
    }
    
    while (i <= srodek - 1) {
    	pom[k++] = wej[i++];
	}
 
    while (j <= prawy) {
    	pom[k++] = wej[j++];
	}
 
    for (i = lewy; i <= prawy; i++) {
    	wej[i] = pom[i];
	}
 
    return wynik;
}

int sortuj(int wej[], int pom[], int lewy, int prawy) {
    int wynik = 0;
    
    if (prawy > lewy) {
        int srodek = (lewy + prawy) / 2;

        wynik += sortuj(wej, pom, lewy, srodek);
        wynik += sortuj(wej, pom, srodek + 1, prawy);
 
        wynik += polacz(wej, pom, lewy, srodek + 1, prawy);
    }
    return wynik;
}
 
int main() {
    int n;
    cin >> n;
    
    int wej[n];
    for (int i = 0; i < n; i++) {
    	cin >> wej[i];
	}
	
	int pom[n];
    cout << sortuj(wej, pom, 0, n - 1);
    return 0;
}
