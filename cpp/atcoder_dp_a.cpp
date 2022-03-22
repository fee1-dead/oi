#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n; cin >> n;
    vector<ll> costs(n + 1);
    vector<ll> heights(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> heights[i];
    }
    costs[0] = 1e6;
    costs[1] = 0;
    for(int i = 2; i <= n; i++) {
        ll currheight = heights[i];
        ll choice1 = abs(currheight - heights[i-2]) + costs[i-2];
        ll choice2 = abs(currheight - heights[i-1]) + costs[i-1];
        costs[i] = min(choice1, choice2);
    }
    cout << costs[n] << "\n";
}