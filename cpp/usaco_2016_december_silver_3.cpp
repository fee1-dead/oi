#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> adj[256];

struct Cow { ll x, y, p; };

Cow cows[256];

// power >= sqrt(xdiff^2 + ydiff^2)
// check if power^2 >= xdiff^2 + ydiff^2
bool reaches(ll thiscow, ll thatcow) {
    ll power = cows[thiscow].p;
    ll xdiff = cows[thiscow].x - cows[thatcow].x;
    ll ydiff = cows[thiscow].y - cows[thatcow].y;

    return (power*power) >= (xdiff*xdiff) + (ydiff*ydiff);
}

bool visited[256];
ll reached = 0;

void dfs(ll cow) {
    if (visited[cow]) {
        return;
    }

    reached++;
    visited[cow] = true;

    for (ll adjacent: adj[cow]) {
        dfs(adjacent);
    }
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    int n;
    cin >> n;

    for (int cow = 0; cow < n; cow++) {
        cin >> cows[cow].x >> cows[cow].y >> cows[cow].p;
    }
    // now build a reachability graph.
    for (int cow = 0; cow < n; cow++) {   
        for (int prevcow = 0; prevcow < n; prevcow++) {
            if (reaches(cow, prevcow)) {
                adj[cow].push_back(prevcow);
            }
        }
    }

    ll ans = 0;

    // we now do a dfs.
    for (int cow = 0; cow < n; cow++) {
        reached = 0;
        fill(begin(visited), end(visited), false);
        dfs(cow);
        ans = max(reached, ans);
    }

    cout << ans << endl;
}
