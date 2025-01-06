/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int S = s.length(), P = p.length();
        vector<vector<int>> dp(S+1, vector<int>(P+1, 0));
        dp[0][0] = 1;
        for(int j=1; j<P+1; j++){
            if(p[j-1]=='*') dp[0][j] = dp[0][j-2];
        }
        for(int i=1; i<S+1; i++){
            for(int j=1; j<P+1; j++){
                if(s[i-1]==p[j-1] || p[j-1]=='.') dp[i][j] = dp[i-1][j-1];
                else if(p[j-1]=='*'){
                    if(p[j-2]==s[i-1] || p[j-2]=='.'){
                        dp[i][j] = dp[i-1][j] || dp[i][j-2];
                    }
                    else dp[i][j] = dp[i][j-2];
                }
            }
        }
        return dp[S][P];
    }
};