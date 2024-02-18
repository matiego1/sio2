#include <iostream>
#include <climits>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
    int n;
    scanf("%d", &n);
    
    int wynik = INT_MIN;
    int mini;
    
    scanf("%d", &mini);
    for (int i = 1; i < n; i++) {
    	int a;
        scanf("%d", &a);
        
        wynik = max(wynik, a - mini);
        mini = min(mini, a);
    }
    
    printf("%d", wynik);

	return 0;
}