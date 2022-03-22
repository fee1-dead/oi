#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> algo(n);
    for(int i = 0; i < n; i++) {
        cin >> algo[i];
    }
    sort(algo.begin(), algo.end());
    for(int i = 0; i < n; i++) {
        if (algo[i] > x) {
            cout << i << endl;
            exit(0);
        }
        x -= algo[i];
    }
    cout << n << endl;
}