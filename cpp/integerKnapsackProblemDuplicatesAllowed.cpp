// C++ program to implement
// unbounded knapsack problem using tabulation
#include <bits/stdc++.h>
using namespace std;

int knapSack(int capacity, vector<int> &val, vector<int> &wt) {

    // 2D matrix for tabulation.
    vector<vector<int>> dp(val.size() + 1, vector<int>(capacity + 1, 0));

    // Calculate maximum profit for each
    // item index and knapsack weight.
    for (int i = val.size() - 1; i >= 0; i--) {
        for (int j = 1; j <= capacity; j++) {

            int take = 0;
            if (j - wt[i] >= 0) {
                take = val[i] + dp[i][j - wt[i]];
            }
            int noTake = dp[i + 1][j];

            dp[i][j] = max(take, noTake);
        }
    }

    return dp[0][capacity];
}

int main() {
  
    vector<int> val = {1, 1}, wt = {2, 1};
    int capacity = 3;
    cout << knapSack(capacity, val, wt);
}
