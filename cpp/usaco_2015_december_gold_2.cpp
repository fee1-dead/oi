#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool achievable_not_half[10000001];
bool achievable_halved[5000001];
int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    int t, a, b; cin >> t >> a >> b;
    achievable_not_half[0] = true;
    for(int i = 0; i <= t; i++) {
        if (achievable_not_half[i]) {
            achievable_halved[i/2] = true;
            if(i + a <= 10000000) 
                achievable_not_half[i + a] = true;
            if(i + b <= 10000000)
                achievable_not_half[i + b] = true;
        }
    }
    for(int i = 0; i <= t; i++) {
        if (achievable_halved[i]) {
            achievable_halved[i + a] = true;
            achievable_halved[i + b] = true;
        }
    }
    for(int i = t; i > 0; i--) {
        if (achievable_halved[i] || achievable_not_half[i]) {
            cout << i << "\n";
            break;
        }
    }
}
