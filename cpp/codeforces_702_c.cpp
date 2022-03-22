#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll cities[100005], towers[100005];
int num_cities, num_towers;

// [min, max] inclusive
ll first_true(ll min, ll max, function<bool(ll)> f) {
    max++;
    while (min < max) {
        ll mid = min + (max - min) / 2;
        if (f(mid)) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }

    return min;
}

bool is_valid(ll r) {
    int curr_city = 0;
    int curr_tower = 0;

    while (curr_city < num_cities && curr_tower < num_towers) {
        if (abs(towers[curr_tower] - cities[curr_city]) <= r) {
            curr_city++;
        } else {
            curr_tower++;
        }
    }

    return curr_city == num_cities;
}

int main() {
    cin >> num_cities >> num_towers;
    for (int i = 0; i < num_cities; i++) cin >> cities[i];
    for (int i = 0; i < num_towers; i++) cin >> towers[i];
    cout << first_true(0, 2e9, is_valid) << endl;
}