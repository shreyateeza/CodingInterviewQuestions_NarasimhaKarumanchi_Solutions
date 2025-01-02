class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums, int K) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        set<vector<int>> temp;
        int N = nums.size();
        for(int i=0; i<N-1; i++){
            int first=i, second=i+1, last=N-1;
            while(second<last){
                int sum = nums[first]+nums[second]+nums[last];
                if(sum == K){
                    temp.insert({nums[first], nums[second], nums[last]});
                    second++, last--;
                }
                else if(sum>K) last--;
                else second++;
            }
        }
        for(auto i: temp) result.push_back(i);
        return result;
    }
};