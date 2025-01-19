#include <bits/stdc++.h>
using namespace std;

// Function to find the length of the longest palindromic subsequence
int lps(const string &s){
    int n = s.size();
    // Create two vectors: one for the current state (dp) and one for the previous state (dpPrev)
    vector<int> dp(n), dpPrev(n);

    // Loop through the string in reverse (starting from the end)
    for (int i = n - 1; i >= 0; --i){
        // A single character is always a palindrome of length 1
        dp[i] = 1;
        // Loop through the characters ahead of i
        for (int j = i + 1; j < n; ++j){
            // If the characters at i and j are the same
            if (s[i] == s[j]){
                // Add 2 to the length of the palindrome between them
                dp[j] = dpPrev[j - 1] + 2;
            }
            else{
                // Take the maximum between excluding either i or j
                dp[j] = max(dpPrev[j], dp[j - 1]);
            }
        }
        // Update dpPrev to the current state of dp for the next iteration
        dpPrev = dp;
    }

    // Answer is the length of longest palindromic subsequence in entire string
    return dp[n - 1];
}

int main(){
    string s = "GEEKSFORGEEKS";
    cout << "The length of the LPS is " << lps(s) << endl;
    return 0;
}
