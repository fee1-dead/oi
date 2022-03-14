#include <bits/stdc++.h>
using namespace std;

vector<int> sameadj[100005];
vector<int> diffadj[100005];

bool bad, visited[100005], grass_type[100005];

// each connected component have two ways
int connected_components;

void dfs(int node, bool node_data=false) {
    visited[node] = true;
    grass_type[node] = node_data;

    for (int adjacent: sameadj[node]) {
        if (visited[adjacent]) {
            if (grass_type[adjacent] != node_data) {
                bad = true;
            }
        } else {
            dfs(adjacent, node_data);
        }
    }

    for (int adjacent: diffadj[node]) {
        if (visited[adjacent]) {
            if (grass_type[adjacent] == node_data) {
                bad = true;
            }
        } else {
            dfs(adjacent, !node_data);
        }
    }
}

int main() {
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);
    int n, m;
    scanf("%i %i\n", &n, &m);
    for (int i = 0; i < m; i++) {
        char c;
        int a, b;
        scanf("%c %i %i\n", &c, &a, &b);
        if (c == 'S') {
            sameadj[a].push_back(b);
            sameadj[b].push_back(a);
        } else {
            diffadj[a].push_back(b);
            diffadj[b].push_back(a);
        }
    }

    for (int i = 1; !bad && i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            connected_components++;
        }
    }

    if (bad) cout << "0" << endl;
    else {
        cout << "1";
        for (int i = 0; i < connected_components; i++) {
            cout << "0";
        }
        cout << endl;
    }
}