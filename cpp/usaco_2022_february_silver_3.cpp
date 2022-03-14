#include <bits/stdc++.h>
using namespace std;

int arr[100005];
pair<int, int> cab_ranges[10005];

int main() {
    int t; cin >> t;

    for (int subtask = 0; subtask < t; subtask++) {
        int m, n, k; cin >> m >> n >> k;

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        for (int cab = 1; cab <= m; cab++) {
            int minIt = 99999999;
            int maxIt = -1;

            for (int i = 0; i < n; i++) {
                if (arr[i] == cab) {
                    if (minIt == 99999999) minIt = i;
                    maxIt = i;
                }
            }

            cab_ranges[cab] = make_pair(minIt, maxIt);
        }

        int i = 0;
        int min_cab = 1;
        for (; min_cab <= m; min_cab++) {
            int cab_max = cab_ranges[min_cab].second;

            for (; i <= cab_max && i < n; i++) {
                if ((arr[i] >= min_cab) && (arr[i] < min_cab + k)) {
                    arr[i] = -1;
                }
            }

            if (i == n) break;

            // we've handled elements in range of this cabinet. Because we have a sliding
            // window we can go some elements back in order to help eliminating emails in
            // other ranges.
            int to_go_back = k - 1;
            int went_back_by = 0;

            for(;;) {
                if (i == 0) break;

                if (went_back_by < to_go_back) {
                    went_back_by++; i--;
                } else { break; }
            }
        }

        min_cab++;
        i--;

        // i points to last element.
        for (; min_cab <= m; min_cab++) {
            int cab_min = cab_ranges[min_cab].first;
            int cab_max = cab_ranges[min_cab].second;
            int hold = 0;

            bool skip = true;
            for (int j = cab_min; j <= cab_max; j++) {
                if (arr[j] == min_cab) skip = false;
            }
            if (skip) continue;

            for (; i >= cab_min && i >= 0; i--) {
                if (arr[i] == -1) continue;

                if ((arr[i] >= min_cab) && (arr[i] < min_cab + k)) {
                    arr[i] = -1;
                } else {
                    hold++;
                    if (hold >= k) {
                        break;
                    }
                }
            }

            // we've handled elements in range of this cabinet. Because we have a sliding
            // window we can go some elements back in order to help eliminating emails in
            // other ranges.
            int to_go_back = k - 1;
            int went_back_by = 0;

            for(;;) {
                if (i >= n) break;

                if (arr[i] == -1) i++;
                else if (went_back_by < to_go_back) {
                    went_back_by++; i++;
                } else { break; }
            }
        }

        bool bad = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] != -1) {
                bad = true;
                break;
            }
        }

        cout << (bad ? "NO" : "YES") << endl;
    }
}