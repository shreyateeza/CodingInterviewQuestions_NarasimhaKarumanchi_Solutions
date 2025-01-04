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
    void binaryTreePathsHelper(TreeNode *root, string temp, vector<string>& result){
        if(!root) return;
        if(!root->left && !root->right){
            string x = to_string(root->val);
            temp+=x;
            result.push_back(temp);
            return;
        }
        string x = to_string(root->val)+"->";
        temp+=x;
        binaryTreePathsHelper(root->left, temp, result);
        binaryTreePathsHelper(root->right, temp, result);
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        string temp;
        binaryTreePathsHelper(root, temp, result);
        return result;
    }
};