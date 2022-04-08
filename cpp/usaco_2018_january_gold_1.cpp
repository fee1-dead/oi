#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define p pair

typedef struct {
    int a, b;
    ll relevance;
} edge;

typedef struct {
    ll threshold;
    int vertex, index;
} query;

edge edges[100000];
query queries[100000];
int answers[100000];

bool cmp_query(query a, query b) {
    return b.threshold < a.threshold;
}

bool cmp_edge(edge a, edge b) {
    return b.relevance < a.relevance;
}

struct Dsu {
    vector<int> e;
    Dsu(int N) { e = vector<int>(N, -1); }
    // get the representative
    int get(int x) {
        if (e[x] < 0) {
            return x;
        } else {
            int r = get(e[x]);
            // compress path
            e[x] = r;
            return r;
        }
    }

    void unite(int a, int b) {
        a = get(a); b = get(b);

        // if less nodes need to travel further when we swap then swap
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b];
        e[b] = a;
    }
};

int main() {
    freopen("mootube.in", "r", stdin); freopen("mootube.out", "w", stdout);
    int n, q; cin >> n >> q;
    for(int i = 0; i < n-1; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].relevance;
    }
    for(int i = 0; i < q; i++) {
        cin >> queries[i].threshold >> queries[i].vertex;
        queries[i].index = i;
    }
    sort(edges, edges + n - 1, cmp_edge);
    sort(queries, queries + q, cmp_query);
    Dsu dsu = Dsu(n);

    int edge_index = 0;
    for(int query_index = 0; query_index < q; query_index++) {
        query qy = queries[query_index];
        ll threshold = qy.threshold;
        while (edge_index < (n - 1) && edges[edge_index].relevance >= threshold)
        {
            dsu.unite(edges[edge_index].a, edges[edge_index].b);
            edge_index++;
        }
        answers[qy.index] = -dsu.e[dsu.get(qy.vertex)] - 1;
    }
    for(int i = 0; i < q; i++) {
        cout << answers[i] << endl;
    }
}