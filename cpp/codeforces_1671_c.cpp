#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve(vector<ll> v, ll X) {
    sort(v.begin(), v.end());

    int total = 0;

    ll x = X;
    for (ll value: v) {
        ll v = value;
        if (x >= v) {
            x -= v;
            total++;
        }
    }
    
    int things_to_buy = total;

    int money_used_without_inflation = X - x;
    int money_left = x;
    ll incr = 0;
    if (things_to_buy) {
        int days = money_left / things_to_buy;
        while(true) {
            incr += days;
            total += days * things_to_buy;
            while ((things_to_buy != 0) && ((X - (money_used_without_inflation + incr * things_to_buy)) / things_to_buy) <= 0) {
                things_to_buy--;
                money_used_without_inflation -= v[things_to_buy];
            }
            if (things_to_buy <= 0)
                break;
            else {
                money_left = X - (money_used_without_inflation + incr * things_to_buy);
                days = money_left / things_to_buy;
            }
        }
    }


    cout << total << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int c; cin >> c;
    for (int i = 0; i < c; i++) {
        int n, x; cin >> n >> x;
        vector<ll> v(n);
        for(int k = 0; k < n;k++) {
            cin >> v[k];
        }
        solve(v, x);
    }
}