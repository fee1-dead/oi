#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int t; cin >> t;
    for(int c = 0; c < t; c++) {
        int n; cin >> n;
        vector<ll> types(n);
        for(int i = 0; i < n; i++) {
            cin >> types[i];
        }
        sort(types.begin(), types.end());
        bool bad = types.size() == 1 && types[0] > 1;
        bad = bad || (types[n-1] - types[n-2]) > 1;
        if(bad) cout <<"NO\n"; else cout << "YES\n";
    }
}