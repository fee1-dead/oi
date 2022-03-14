#include <bits/stdc++.h>
using namespace std;

int diff[1000005];

int main() {
    int n, k; cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        diff[a]++; diff[b+1]--;
    }

    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i-1];
    }

    sort(diff+1, diff+n+1);

    cout << diff[(n+1) / 2] << endl;
}

