#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll freq[200005];
int main() {
    int n; cin >> n;
    ll prefix_sum = 0;
    ll ans = 0;
    freq[0] = 1;
    for (int i = 1; i <= n; i++) {
        ll num; cin >> num;
        num %= n;
        prefix_sum = (((prefix_sum + num) % n) + n) % n;
        freq[prefix_sum]++;
    }
    for (ll x: freq) {
        ans += (x * (x - 1)) / 2;
    }
    cout << ans << endl;
}