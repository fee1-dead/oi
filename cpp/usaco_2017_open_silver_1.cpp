#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define f first
#define s second

int main() {
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);

    ll n; cin >> n;
    vector<pair<ll, ll>> outputs;
    outputs.reserve(n);
    for (int i = 0; i < n; i++) {
        ll numcows, time; cin >> numcows >> time;
        outputs.push_back(make_pair(time, numcows));
    }

    sort(outputs.begin(), outputs.end());

    pair<ll, ll>* front = &(*outputs.begin());
    pair<ll, ll>* back = (&(*outputs.end())) - 1;

    ll max_time = 0;
    
    while (front < back) {
        ll time_a = (*front).f;
        ll time_b = (*back).f;
        max_time = max(time_a + time_b, max_time);
        ll decrease_by = min((*front).s, (*back).s);
        (*front).s -= decrease_by;
        (*back).s -= decrease_by;
        if ((*front).s == 0) {
            front++;
        }
        if ((*back).s == 0) {
            back--;
        }
    }

    cout << max_time << endl;
}