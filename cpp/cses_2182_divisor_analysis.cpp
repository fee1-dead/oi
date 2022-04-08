#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll binpow(ll base, ll exp, ll modulo) {
    ll accum = 1;
    ll accum_prod = base;
    while(exp) {
        if (exp&1) accum = accum * accum_prod % modulo;
        accum_prod *= accum_prod;
        accum_prod %= modulo;
        exp>>=1;
    }
    return accum;
}
int main() {
    // mmmmmm, number theory
    // https://www2.math.upenn.edu/~deturck/m170/wk3/lecture/sumdiv.html

    ll num_divisors = 1;
    ll sum_divisors = 1;
    ll prod_divisors = 1;
    ll mod = 1e9+7;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        ll x; ll k; cin >> x >> k;
        num_divisors = (num_divisors * (k+1)) % mod;
        sum_divisors = (sum_divisors * binpow(x, k * (k + 1) / 2, mod)) % mod;
        prod_divisors = (prod_divisors * binpow(x, k, mod)) * mod;
    }

    cout << num_divisors << " " << sum_divisors << " " << prod_divisors << "\n";
}