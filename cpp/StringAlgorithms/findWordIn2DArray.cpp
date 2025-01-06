class Solution {
public:
    bool solve(int idx, int i, int j, vector<vector<char>>& board, string word){
        if(idx == word.length()) return true;
        if(i<0 || i>=board.size() || j>=board[0].size() || j<0) return false;
        if(board[i][j] == word[idx]){
            board[i][j] = '.';
            if(solve(idx+1, i+1, j, board, word) || solve(idx+1, i-1, j, board, word) || solve(idx+1, i, j+1, board, word) || solve(idx+1, i, j-1, board, word)) return true;
            board[i][j] = word[idx];
        }
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int N1 = board.size(), N2 = board[0].size();
        for(int i=0; i<N1; i++){
            for(int j=0; j<N2; j++){
                if(board[i][j] == word[0]){
                    if(solve(0, i, j, board, word)){
                        return true;
                    }
                }
            }
        }
        return false;        
    }
};