/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int N = p.length(), M = s.length();
        vector<bool> cur(M+1, false), prev(M+1, false);
        prev[0] = true;
        for(int i=1; i<=N; i++){
            if(p[i-1]=='*') cur[0] = prev[0];
            else cur[0] = false;
            for(int j=1; j<=M; j++){
                if(p[i-1]==s[j-1] || p[i-1]=='?'){
                    cur[j] = prev[j-1];
                }
                else if(p[i-1]=='*'){
                    cur[j] = prev[j] || cur[j-1];
                }
                else cur[j] = false;
            }
            prev = cur;
        }
        return prev[M];
    }
};