class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int N = nums.size();
        vector<int> result;
        multiset<int, greater<int>> ms;
        for(int i=0; i<N; i++){
            ms.insert(nums[i]);
            if(i >= k) ms.erase(ms.find(nums[i-k]));
            if(i >= k-1) result.push_back(*ms.begin());
        }
        return result;
    }
};