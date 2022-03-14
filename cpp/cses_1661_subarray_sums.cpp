#include <bits/stdc++.h>
using namespace std;
using ll = long long;
map<ll, int> psums;
int main() {
    int n; ll x;
    cin >> n >> x;
    ll sum = 0;
    ll subarrays = 0;
    psums[0] = 1;
    for (int i = 0; i < n; i++) {
        ll num; cin >> num;
        sum += num;
        subarrays += psums[sum - x];
        psums[sum] += 1;
    }
    cout << subarrays << endl;
}