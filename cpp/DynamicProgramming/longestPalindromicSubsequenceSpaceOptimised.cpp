#include <bits/stdc++.h>
using namespace std;

// Function to find the length of the longest palindromic subsequence
int lps(const string &s){
    int n = s.size();
    // Create two vectors: one for the current state (curr) and one for the previous state (prev)
    vector<int> curr(n), prev(n);

    // Loop through the string in reverse (starting from the end)
    for (int i = n - 1; i >= 0; --i){
        // A single character is always a palindrome of length 1
        curr[i] = 1;
        // Loop through the characters ahead of i
        for (int j = i + 1; j < n; ++j){
            // If the characters at i and j are the same
            if (s[i] == s[j]){
                // Add 2 to the length of the palindrome between them
                curr[j] = prev[j - 1] + 2;
            }
            else{
                // Take the maximum between excluding either i or j
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        // Update prev to the current state of curr for the next iteration
        prev = curr;
    }

    // Answer is the length of longest palindromic subsequence in entire string
    return curr[n - 1];
}

int main(){
    string s = "GEEKSFORGEEKS";
    cout << "The length of the LPS is " << lps(s) << endl;
    return 0;
}
