/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBSTUtil(vector<int>& nums, int start, int end){
        int mid = (start+end)/2;
        return start>=end? NULL : new TreeNode(nums[mid], sortedArrayToBSTUtil(nums, start, mid), sortedArrayToBSTUtil(nums, mid+1, end)); 
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBSTUtil(nums, 0, nums.size());
    }
};