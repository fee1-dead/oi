#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll binpow(ll base, ll exp, ll modulo) {
    ll accum = 1;
    ll accum_prod = base;
    while (exp) {
        if(exp&1) accum = accum * accum_prod % modulo;
        accum_prod = accum_prod * accum_prod % modulo;
        exp>>=1;
    }
    return accum;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        ll a, b, c; cin >> a >> b >> c;
        cout << binpow(a, binpow(b, c, 1e9+6), 1e9+7) << endl;
    }
}