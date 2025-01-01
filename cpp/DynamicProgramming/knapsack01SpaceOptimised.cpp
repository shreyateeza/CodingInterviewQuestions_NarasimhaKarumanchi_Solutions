#include <iostream>
#include <vector>
using namespace std;

// Function to find the maximum profit
int knapSack(int W, vector<int>& wt, vector<int>& val) {
  
    // Making and initializing dp vector
    vector<int> dp(W + 1, 0);

    for (int i = 1; i <= wt.size(); i++) {
        for (int w = W; w >= 0; w--) {
            if (wt[i - 1] <= w)
              
                // Finding the maximum value
                dp[w] = max(dp[w], dp[w - wt[i - 1]] + val[i - 1]);
        }
    }
    return dp[W];
}

// Driver code
int main() {
    vector<int> profit = {60, 100, 120};
    vector<int> weight = {10, 20, 30};
    int W = 50;

    cout << knapSack(W, weight, profit) << endl;
    return 0;
}
