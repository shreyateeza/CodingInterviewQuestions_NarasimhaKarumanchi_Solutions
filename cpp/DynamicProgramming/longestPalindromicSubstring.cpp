class Solution {
public:
    string longestPalindrome(string s) {
        int N = s.length(), maxLen=1, max_i, max_j;
        for(int i=0; i<N; i++){
            int start=i, end=i;
            while(start>=0 && end<N){
                if(s[start] == s[end]){
                    start--;
                    end++;
                }
                else break;
            }
            if(end-start > maxLen){
                maxLen = end-start;
                max_i = start;
                max_j = end;
            }
            start=i, end=i+1;
            while(start>=0 && end<N){
                if(s[start] == s[end]){
                    start--;
                    end++;
                }
                else break;
            }
            if(end-start > maxLen){
                maxLen = end-start;
                max_i = start;
                max_j = end;
            }
        }
        string result = "";
        for(int i=max_i+1; i<max_j; i++) result += s[i];
        return result;        
    }
};
