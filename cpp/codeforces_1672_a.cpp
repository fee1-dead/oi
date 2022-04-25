#include <bits/stdc++.h>
using namespace std;

void solve() {
    int num; cin >> num;
    int res = 0;
    for (int i = 0; i < num; i++) {
        int t; cin >> t;
        res = ((res + t - 1) % 2);
    }
    cout << (res? "errorgorn\n" : "maomao90\n");
}

int main() {
    int c; cin >> c;
    for (int i = 0; i < c; i++) {
        solve();
    }
}

