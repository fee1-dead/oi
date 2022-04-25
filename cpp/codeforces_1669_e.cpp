#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(vector<string> s) {
    int len = s.size();
    vector<vector<ll>> fcsc;
    for (int i = 0; i < 11; i++) {
        vector<ll> vv;
        vv.resize(11);
        fcsc.push_back(vv);
    }
    vector<ll> fcc;
    vector<ll> scc;
    fcc.resize(11);
    scc.resize(11);
    ll ans = 0;
    for (int i = len - 1; i >= 0; i--) {
        auto ss = s[i];
        auto fc = ss[0] - 'a';
        auto sc = ss[1] - 'a';
        fcsc[fc][sc]++;
        fcc[fc]++;
        scc[sc]++;
        ll numwithfc = fcc[fc] - 1;
        ll numwithsc = scc[sc] - 1;
        ll nummatches = fcsc[fc][sc] - 1;
        ans += numwithfc - nummatches;
        ans += numwithsc - nummatches;
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int cases;
    cin >> cases;
    for (int i = 0; i < cases; i++) {
        int n; cin >> n;
        vector<string> v(n);
        for (int j = 0; j < n; j++) {
            cin >> v[j];
        }
        solve(v);
    }
}

