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

// Code 2

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isInterleaved(string s1, string s2, string s3) {
    int m = s1.length();
    int n = s2.length();

    // If the combined length doesn't match, it's impossible
    if (m + n != s3.length()) return false;

    // dp[i][j] will be true if s3[0..i+j-1] is an interleaving of s1[0..i-1] and s2[0..j-1]
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Base case: two empty strings form an empty string
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            }
            // If s1 is empty, check if s2 matches s3
            else if (i == 0) {
                dp[i][j] = (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
            // If s2 is empty, check if s1 matches s3
            else if (j == 0) {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
            }
            // If characters of both s1 and s2 match s3
            else {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                           (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    string s1 = "abc";
    string s2 = "def";
    string s3 = "adbcef";

    if (isInterleaved(s1, s2, s3)) {
        cout << s3 << " is a valid interleaving of " << s1 << " and " << s2 << endl;
    } else {
        cout << s3 << " is NOT a valid interleaving." << endl;
    }

    return 0;
}

// code 3

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Structure to hold the state of our exploration
struct State {
    int i;          // Index in s1
    int j;          // Index in s2
    string current; // Interleaved string built so far
};

void printInterleavingsIterative(string s1, string s2) {
    stack<State> s;
    
    // Start with an empty string and indices at 0
    s.push({0, 0, ""});

    while (!s.empty()) {
        State top = s.top();
        s.pop();

        // If both strings are fully processed, print the result
        if (top.i == s1.length() && top.j == s2.length()) {
            cout << top.current << endl;
            continue;
        }

        /* To maintain the same order as the recursive version, 
           we push the 's2' choice first so the 's1' choice 
           is processed first (LIFO).
        */

        // Choice: Take from s2
        if (top.j < s2.length()) {
            s.push({top.i, top.j + 1, top.current + s2[top.j]});
        }

        // Choice: Take from s1
        if (top.i < s1.length()) {
            s.push({top.i + 1, top.j, top.current + s1[top.i]});
        }
    }
}

int main() {
    string s1 = "AB";
    string s2 = "CD";

    cout << "Iterative interleavings of " << s1 << " and " << s2 << ":" << endl;
    printInterleavingsIterative(s1, s2);

    return 0;
}

// code 4

#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct State {
    int i, j;
    string current;
};

void printInterleavingsBFS(string s1, string s2) {
    queue<State> q;
    q.push({0, 0, ""});

    int targetLength = s1.length() + s2.length();

    while (!q.empty()) {
        State head = q.front();
        q.pop();

        // If we've reached the target length, we found a complete interleaving
        if (head.current.length() == targetLength) {
            cout << head.current << endl;
            continue;
        }

        // Try adding from s1
        if (head.i < s1.length()) {
            q.push({head.i + 1, head.j, head.current + s1[head.i]});
        }

        // Try adding from s2
        if (head.j < s2.length()) {
            q.push({head.i, head.j + 1, head.current + s2[head.j]});
        }
    }
}

int main() {
    string s1 = "AB";
    string s2 = "CD";

    cout << "BFS (Queue) Interleavings of " << s1 << " and " << s2 << ":" << endl;
    printInterleavingsBFS(s1, s2);

    return 0;
}