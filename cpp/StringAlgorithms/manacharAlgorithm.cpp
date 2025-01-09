#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string manacher(string s) {
    string T = "#";
    for (char c : s) {
        T += c;
        T += '#';
    }
    int n = T.length();
    vector<int> P(n, 0);
    int C = 0, R = 0;
    for (int i = 0; i < n; i++) {
        int mirr = 2 * C - i;
        if (i < R)
            P[i] = min(R - i, P[mirr]);
        // Attempt to expand palindrome centered at i
        int a = i + (1 + P[i]);
        int b = i - (1 + P[i]);
        while (a < n && b >= 0 && T[a] == T[b]) {
            P[i]++;
            a++;
            b--;
        }
        // If palindrome centered at i expands past R, adjust center and right boundary
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
    // Find the maximum element in P
    int maxLen = *max_element(P.begin(), P.end());
    int centerIndex = find(P.begin(), P.end(), maxLen) - P.begin();
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    string s = "babad";
    string longestPalindrome = manacher(s);
    cout << "Longest Palindromic Substring: " << longestPalindrome << endl;
    return 0;
}
