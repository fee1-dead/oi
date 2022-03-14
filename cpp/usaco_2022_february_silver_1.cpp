#include <bits/stdc++.h>
using namespace std;

// immutable
int cow2gift2rank[505][505];
int cow2rank2gift[505][505];

// mutable
int cow2gift[505];
int gift2cow[505];

bool satisfied[505], gift_taken[505];


int main() {
    int n; cin >> n;

    for (int cow = 1; cow <= n; cow++) {
        for (int pref = 0; pref < n; pref++) {
            int gift; cin >> gift;

            cow2gift2rank[cow][gift] = pref;
            cow2rank2gift[cow][pref] = gift;
        }
    }

    for (int i = 1; i <= n; i++) {
        cow2gift[i] = i;
        gift2cow[i] = i;
    }

    bool progress = false;

    do {
        progress = false;

        // look for unsatisfied cows
        for (int cow = 1; cow <= n; cow++) {
            if (satisfied[cow]) continue;
            
            int best_rank = 9999;

            // find best ranked, gift not taken for cow
            for (int gift = 1; gift <= n; gift++) {
                if (gift_taken[gift]) continue;

                // NB. lower rank is better
                best_rank = min(cow2gift2rank[cow][gift], best_rank);
            }

            int best_gift = cow2rank2gift[cow][best_rank];

            // if already got best, cow is satisfied
            if (best_gift == cow2gift[cow]) {
                satisfied[cow] = true;
                gift_taken[best_gift] = true;
                progress = true;
                continue;
            }

            // if another cow has my best choice, attempt to swap with them.
            // because they want their best choice, swapping with them when they do not have their best choice could be suboptimal
            int cow_b = gift2cow[best_gift];
            int best_rank_for_cow_b = 9999;
    
            // find best ranked, gift not taken for cow
            for (int gift = 1; gift <= n; gift++) {
                if (gift_taken[gift]) continue;

                // NB. lower rank is better
                best_rank_for_cow_b = min(cow2gift2rank[cow_b][gift], best_rank_for_cow_b);
            }
            int best_gift_for_cow_b = cow2rank2gift[cow_b][best_rank_for_cow_b];
            int my_gift = cow2gift[cow];

            if (best_gift_for_cow_b == my_gift) {
                cow2gift[cow_b] = my_gift;
                gift2cow[my_gift] = cow_b;
                cow2gift[cow] = best_gift;
                gift2cow[best_gift] = cow;

                satisfied[cow] = true;
                satisfied[cow_b] = true;
                gift_taken[my_gift] = true;
                gift_taken[best_gift] = true;
                progress = true;
                continue;
            }
        }
    } while(progress);

    for (int i = 1; i <= n; i++) {
        cout << cow2gift[i] << endl;
    }
}