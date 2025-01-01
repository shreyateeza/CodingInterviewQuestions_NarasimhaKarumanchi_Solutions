class Solution {
public:
    int jump(vector<int>& nums) {
        int N = nums.size(), answer = 0, curEnd = 0, curFar = 0;
        for(int i=0; i<N-1; i++){
            curFar = max(i+nums[i], curFar);
            if(curEnd == i){
                answer++;
                curEnd = curFar;
            }
        }
        return answer;
    }
};