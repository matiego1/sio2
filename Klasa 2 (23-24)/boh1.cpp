#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

vector<tuple<int, int, int>> dodatnie;
vector<tuple<int, int, int>> ujemne;
vector<int> wynik;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    long long z;
    cin >> n >> z;

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;

        if (a <= b) {
            dodatnie.push_back(make_tuple(a, b, i));
        } else {
            ujemne.push_back(make_tuple(b, a, i));
        }
    }

    sort(dodatnie.begin(), dodatnie.end());
    sort(ujemne.begin(), ujemne.end());

    for (int i = 0; i < dodatnie.size(); i++) {
        wynik.push_back(get<2>(dodatnie[i]));

        z -= get<0>(dodatnie[i]);

        if (z <= 0) {
            cout << "NIE";
            return 0;
        }

        z += get<1>(dodatnie[i]);
    }

    for (int i = ujemne.size() - 1; i >= 0; i--) {
        wynik.push_back(get<2>(ujemne[i]));

        z -= get<1>(ujemne[i]);

        if (z <= 0) {
            cout << "NIE";
            return 0;
        }

        z += get<0>(ujemne[i]);
    }

    cout << "TAK\n";
    for (int i = 0; i < wynik.size(); i++) {
        cout << wynik[i] << " ";
    }

    return 0;
}