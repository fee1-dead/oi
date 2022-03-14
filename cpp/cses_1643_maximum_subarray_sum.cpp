#include <bits/stdc++.h>
using namespace std;
long long val[200005];
int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    long long vMin = 0;
    long long vAns = LLONG_MIN;
    for (int i = 1; i <= n; i++) {
        val[i] += val[i-1];
        vAns = max(val[i] - vMin, vAns);
        vMin = min(val[i], vMin);
    }

    cout << vAns << endl;
}