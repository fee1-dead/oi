#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, q; cin >> n >> q;
    vector<ll> psum = vector<ll>(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> psum[i];
        psum[i] += psum[i-1];
    }
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        cout << psum[r] - psum[l] << endl;
    }
}