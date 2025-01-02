class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        vector<vector<int>> result;
        set<vector<int>> st;
        int diff = INT_MAX;
        sort(nums.begin(), nums.end());
        int N = nums.size();
        for(int i=0; i<N-2; i++){
            int first = i, second = i+1, last=N-1;
            while(second<last){
                int sum = nums[first]+nums[second]+nums[last];
                if(abs(target-sum)<abs(diff)){
                    diff = target-sum;
                }
                if(sum<target){
                    second++;
                }
                else last--;
            }
        }
        return (target-diff);
    }
};