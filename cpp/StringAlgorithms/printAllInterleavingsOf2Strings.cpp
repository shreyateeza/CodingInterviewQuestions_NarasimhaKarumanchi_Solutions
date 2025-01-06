#include <bits/stdc++.h>
using namespace std;

// Function to print interleavings of two strings
void printInterleavings(string str1, string str2)
{
    int m = str1.length();
    int n = str2.length();

    // Create a 2D vector to store interleavings
    vector<vector<vector<string> > > dp(
        m + 1, vector<vector<string> >(n + 1));

    // Base cases: If one of the strings is empty,
    // return the other string
    for (int i = 0; i <= m; i++) {
        dp[i][0] = { str1.substr(0, i) };
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = { str2.substr(0, j) };
    }

    // Fill in the dynamic programming table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // Append the current character of str1 to
            // each interleaved string from previous cells
            dp[i][j] = dp[i - 1][j];
            for (string& s : dp[i][j]) {
                s += str1[i - 1];
            }

            // Append the current character of str2 to each
            // interleaved string from previous cells
            for (string& s : dp[i][j - 1]) {
                dp[i][j].push_back(s + str2[j - 1]);
            }
        }
    }

    // Print all interleavings
    for (const string& interleaved : dp[m][n]) {
        cout << interleaved << endl;
    }
}

// Example usage
int main()
{
    string str1 = "AB";
    string str2 = "CD";
    printInterleavings(str1, str2);
    return 0;
}
