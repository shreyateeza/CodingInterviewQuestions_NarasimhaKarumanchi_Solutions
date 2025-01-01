class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int N = nums.size(), zeroes = 0;
        for(int i=0; i<N; i++){
            if(nums[i] != 0) nums[zeroes++] = nums[i];
        }
        for(int i=zeroes; i<N; i++) nums[i] = 0;
    }
};
