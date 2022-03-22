// mix start(+1) and end(-1) points to one list and
// sort it, the answer is the maximum running sum.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pl = pair<ll, ll>;
pl val[400000];
int main() {
    int n; cin >> n;
    for(int i = 0; i < n * 2; i += 2) {
        int a, b;
        cin >> a >> b;
        val[i] = {a, 1};
        val[i+1] = {b, -1};
    }

    sort(val, val + n * 2);

    ll sum = 0;
    ll maxsum = 0;
    for (int i = 0; i < n * 2; i++) {
        sum += val[i].second;
        maxsum = max(sum, maxsum);
    }
    cout << maxsum << endl;
}