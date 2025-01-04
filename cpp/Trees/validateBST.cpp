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
    bool isValidBSTUtil(TreeNode* root, long minm, long maxm){
        if(!root) return true;
        if(minm >= root->val || root->val >= maxm) return false;
       return isValidBSTUtil(root->left, minm, root->val) && isValidBSTUtil(root->right, root->val, maxm);
    }

    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        if(!root->left && !root->right) return true;
        return isValidBSTUtil(root, (long)INT_MIN-1, (long)INT_MAX+1);        
    }
};