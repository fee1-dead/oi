#include <bits/stdc++.h>
using namespace std;

void solve(vector<long long> v, int bits) {
    long long res = 0;
    for (int bit = 30; bit >= 0; bit--) {
        int req = 0;
        for (auto n: v) {
            if ((n & (1 << bit)) == 0) {
                req++;
            }
        }
        if (req <= bits) {
            bits -= req;
            res = res | (1 << bit);
        }
    }
    cout << res << "\n";
}

int main() {
    int c; cin >> c;
    for(int i = 0; i < c; i++) {
        int a, b; cin >> a >> b;
        vector<long long> s(a);
        for (int k = 0; k < a; k++) {
            cin >> s[k];
        }
        solve(s, b);
    }
}