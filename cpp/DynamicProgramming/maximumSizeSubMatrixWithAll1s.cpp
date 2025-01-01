class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m=matrix.size(), n=matrix[0].size(), ans=0;
        stack<int>s;
        vector<int>dp(n,0);
        int i, j; 
        for( i=0; i<m; i++){
            for( j=0; j<n; j++){
                if(matrix[i][j]!='0') dp[j]+=1;
                else dp[j]=0;
            }
            stack<int> st;
            dp.push_back(0);
            int sum = 0;
            for(int i=0; i<dp.size(); i++){
                if(st.empty() || dp[i]>=dp[st.top()]){
                    st.push(i);
                }
                else{
                    int temp = st.top();
                    st.pop();
                    sum = max(sum, dp[temp]*(st.empty()?i:i-st.top()-1));
                    i--;
                }
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
