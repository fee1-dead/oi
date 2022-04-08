#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    for(int c = 0; c < t; c++) {
        int n; cin >> n;
        vector<int> v(n);
        int zero = -1;
        for(int i = 0; i < n; i++) {
            cin >> v[i];
            if(v[i]==0) {
                if(zero == -1) zero = i;
                else {
                    int mid = n / 2;
                    if (abs(zero - mid) < abs(i-mid)) {
                        zero = i;
                    }
                }
            }
        }

    }
}

void solve(vector<int> v) {

}