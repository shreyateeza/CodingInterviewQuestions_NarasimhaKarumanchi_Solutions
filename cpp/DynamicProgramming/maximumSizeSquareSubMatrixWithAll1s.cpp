class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int N1 = matrix.size(), N2 = matrix[0].size();
        vector<vector<int>> dp(N1+1, vector<int>(N2+1, 0));
        int answer = 0;
        for(int i=1; i<=N1; i++){
            for(int j=1; j<=N2; j++){
                if(matrix[i-1][j-1] == '1'){
                    dp[i][j] = 1;
                    int minm = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    dp[i][j] = minm + 1;
                    answer = max(answer, dp[i][j]);
                }
            }
        }
        return answer*answer;
    }
};
