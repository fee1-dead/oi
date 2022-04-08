#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct edge {
    int a, b;
    ll moo;
};

bool dec_moo(edge& a, edge& b) {
    return b.moo < a.moo;
}

struct Dsu {
    vector<int> e;
    Dsu(int n) { e = vector<int>(n, -1); }
    int get(int node) {
        if (e[node] < 0) {
            return node;
        } else {
            int repr = get(e[node]);
            e[node] = repr;
            return repr;
        }
    }
    bool unite(int a, int b) {
        a = get(a); b = get(b);
        if (a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main() {
    int n; cin >> n;
    vector<edge> edges(n);
    for(int i = 0; i < n; i++) {
        edges[i].a = i;
        cin >> edges[i].b >> edges[i].moo;
        edges[i].b--;
    }
    sort(edges.begin(), edges.end(), dec_moo);
    ll ans = 0;
    Dsu dsu = Dsu(n);
    for(edge e: edges) {
        if(dsu.unite(e.a, e.b)) {
            ans += e.moo;
        }
    }
    cout << ans << "\n";
}