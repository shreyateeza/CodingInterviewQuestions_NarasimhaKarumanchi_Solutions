// C++ program to find out
// maximum value from a given
// sequence of coins using Tabulation
#include <bits/stdc++.h>
using namespace std;

int maxAmount(vector<int> &arr) {
      int n = arr.size();
    // Create a table to store solutions of subproblems
    int dp[n][n];

    // Fill table using above recursive formula. Note that the table is filled in diagonal fashion,
    // from diagonal elements to table[0][n-1] which is the result.
    for (int gap = 0; gap < n; ++gap) {
        for (int i = 0, j = gap; j < n; ++i, ++j) {
            // Here x is value of F(i+2, j),
            // y is F(i+1, j-1) and
            // z is F(i, j-2) in above recursive
            // formula
            int x = ((i + 2) <= j) ? dp[i + 2][j] : 0;
            int y = ((i + 1) <= (j - 1)) ? dp[i + 1][j - 1] : 0;
            int z = (i <= (j - 2)) ? dp[i][j - 2] : 0;
            dp[i][j] = max(arr[i] + min(x, y), arr[j] + min(y, z));
        }
    }
    return dp[0][n - 1];
}

int main() {
    vector<int> arr = {5, 3, 7, 10};
    int res = maxAmount(arr);
    cout << res;
    return 0;
}
