// https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/ 

// C++ program to implement unbounded knapsack problem using space optimised
#include <bits/stdc++.h>
using namespace std;

int knapSack(int capacity, vector<int> &val, vector<int> &wt) {
    // 1D matrix for tabulation.
    vector<int> dp(capacity + 1, 0);
    // Calculate maximum profit for each item index and knapsack weight.
    for (int i = val.size() - 1; i >= 0; i--) {
        for (int j = 1; j <= capacity; j++) {
            int take = 0;
            if (j - wt[i] >= 0) {
                take = val[i] + dp[j - wt[i]];
            }
            int noTake = dp[j];
            dp[j] = max(take, noTake);
        }
    }
    return dp[capacity];
}

int main() { 
    vector<int> val = {1, 1}, wt = {2, 1};
    int capacity = 3;
    cout << knapSack(capacity, val, wt);
}