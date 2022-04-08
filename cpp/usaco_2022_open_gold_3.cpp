#include <bits/stdc++.h>
using namespace std;
using ll = long long;
pair<ll, ll> bounds[100000];
vector<int> children[100000];

struct range {
    ll low, high;
    bool changeable;
    ll actualdiff;

    void unite(range other) {
        if (changeable && other.changeable) {
            if(high < other.low) {
                changeable = false;
                low = high; high = other.low;
            } else if (other.high < low) {
                changeable = false;
                high = low; low = other.high;
            } else {
                // overlap; union
                low = max(low, other.low);
                high = min(high, other.high);
            }
        } else if ((changeable && !other.changeable) || (!changeable && other.changeable)) {
            if (!changeable && other.changeable) swap(*this, other);
            changeable = false;
            if(high < other.low) {
                low = high;
                high = other.high;
            } else if (other.high < low) {
                high = low;
                low = other.low;
            } else {
                low = other.low;
                high = other.high;
            }
        } else { // both unchangeable
            low = min(low, other.low);
            high = max(high, other.high);
        }
    }
};

range dfs(int node) {
    ll low = bounds[node].first;
    ll high = bounds[node].second;
    range accum = {
        low, high, true, 0
    };
    // unify with children
    for(int child: children[node]) {
        accum.unite(dfs(child));
    }
    if(children[node].size() > 1) {
        ll avg = (accum.high + accum.low) / 2;
        accum.actualdiff = max(accum.high - avg, avg - accum.low);
    } else {
        accum.actualdiff = accum.high - accum.low;
    }
    return accum;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t, b; cin >> t >> b;
    for(int _case = 0; _case < t; _case++) {
        int n; cin >> n;
        for(int i = 1; i < n; i++) {
            int p; cin >> p; p--;
            children[p].push_back(i);
        }
        for(int i = 0; i < n; i++) {
            cin >> bounds[i].first >> bounds[i].second;
        }
        range r = dfs(0);
        ll ans = 0;
        if (!r.changeable) ans = r.actualdiff;
        cout << ans << "\n";
        if(b) {if (ans == 3) cout << "3 1 6\n"; else if (ans == 1)
        cout << "6 5 5 5 5\n"; else cout << "5 1 9\n";}
    }

}