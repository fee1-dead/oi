#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll binpow(ll base, ll exp) {
    ll accum = 1;
    ll accum_exp = base;
    while (exp != 0) {
        if (exp & 1) {
            accum *= accum_exp;
            accum %= 1000000007;
        }
        exp >>= 1;
        accum_exp *= accum_exp;
        accum_exp %= 1000000007;
    }
    return accum;
}

int main() {
    int cases; cin >> cases;
    for(int i = 0; i < cases; i++) {
        ll a, b; cin >> a >> b;
        cout << binpow(a, b) << endl;
    }
}