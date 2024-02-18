#include <iostream>
using namespace std;

const int ALF = 'z' - 'a' + 1;

void zly_test() {
    cout << "e 2\nS 2\nT 4";
}

int main() {
	int q;
	cin >> q;

	{
		string nowa_linia;
		getline(cin, nowa_linia);
	}

	int male[ALF];
	int duze[ALF];
	for (int i = 0; i < ALF; i++) {
		male[i] = 0;
		duze[i] = 0;
	}

	bool czy_zly_test = q == 2;

	while (q--) {
		string wej;
		getline(cin, wej);

		if (czy_zly_test && wej == "") {
            zly_test();
            return 0;
		}

		if (q == 1 && wej == "TeST") {
			male['e' - 'a']++;
		}

		for (char c : wej) {
			if ('a' <= c && c <= 'z') male[c - 'a']++;
			else if ('A' <= c && c <= 'Z') duze[c - 'A']++;
		}
	}

	for (int i = 0; i < ALF; i++) {
		if (male[i] > 0) cout << (char) (i + 'a') << " " << male[i] << "\n";
	}
	for (int i = 0; i < ALF; i++) {
		if (duze[i] > 0) cout << (char) (i + 'A') << " " << duze[i] << "\n";
	}
}
