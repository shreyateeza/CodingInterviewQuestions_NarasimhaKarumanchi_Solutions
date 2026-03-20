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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return false;
        if(targetSum == root->val && !root->left && !root->right) return true;
        return hasPathSum(root->left, targetSum-root->val) || hasPathSum(root->right, targetSum-root->val);        
    }
};

#include <stack>
#include <utility> // for pair

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;

        // Stack stores a pair: {Current Node, Remaining Sum needed}
        stack<pair<TreeNode*, int>> st;
        st.push({root, targetSum - root->val});

        while (!st.empty()) {
            pair<TreeNode*, int> current = st.top();
            st.pop();

            TreeNode* node = current.first;
            int remainingSum = current.second;

            // Check if it's a leaf node and the path sum matches
            if (!node->left && !node->right && remainingSum == 0) {
                return true;
            }

            // Push right child first so left child is processed first (standard DFS)
            if (node->right) {
                st.push({node->right, remainingSum - node->right->val});
            }
            if (node->left) {
                st.push({node->left, remainingSum - node->left->val});
            }
        }

        return false;
    }
};