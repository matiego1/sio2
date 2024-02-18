#include <iostream>
#include <set>
#include <climits>
#define ll unsigned long long
using namespace std;

set<ll> zbior;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    while (n--) {
        string typ;
        cin >> typ;

        if (typ == "+") {
            ll a;
            cin >> a;
            zbior.insert(a);
        } else if (typ == "-") {
            ll a;
            cin >> a;
            zbior.erase(a);
        } else if (typ == "f") {
            ll a;
            cin >> a;
            auto x = zbior.lower_bound(a);
            if (x == zbior.end()) {
                cout << "BRAK\n";
            } else {
                cout << *x << "\n";
            }
        } else if (typ == "s") {
            cout << zbior.size() << "\n";
        } else if (typ == "w") {
            for (ll x : zbior) {
                cout << x << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
