// C++ program for implementation of
// optimal binary search tree using tabulation

#include <bits/stdc++.h>
using namespace std;

// A utility function to get sum of
// array elements freq[i] to freq[j]
int sum(vector<int> &freq, int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

// A Dynamic Programming based function that calculates the
// minimum cost of a Binary Search Tree.
int optimalSearchTree(vector<int> &keys, vector<int> &freq) {
  
    int n = keys.size();

    // Create an auxiliary 2D matrix to store 
      // results of subproblems
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // dp[i][j] = Optimal cost of binary search tree
    // that can be formed from keys[i] to keys[j].
    // dp[0][n-1] will store the resultant dp

    // For a single key, dp is equal to frequency of the key
    for (int i = 0; i < n; i++) {
        dp[i][i] = freq[i];
    }

    // Now we need to consider chains of length 2, 3, ... .
    // l is chain length.
    for (int l = 2; l <= n; l++) {
      
        // i is row number in dp[][]
        for (int i = 0; i <= n - l; i++) {
          
            // Get column number j from row number i
              // and chain length l
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            int fsum = sum(freq, i, j);

            // Try making all keys in interval keys[i..j] as root
            for (int r = i; r <= j; r++) {
              
                // c = dp when keys[r] becomes root of this subtree
                int c = ((r > i) ? dp[i][r - 1] : 0) + ((r < j) ? dp[r + 1][j] : 0) + fsum;
                if (c < dp[i][j]) {
                    dp[i][j] = c;
                }
            }
        }
    }

    return dp[0][n - 1];
}
int main() {

    vector<int> keys = {10, 12, 20};
    vector<int> freq = {34, 8, 50};
    cout << optimalSearchTree(keys, freq);
    return 0;
}
