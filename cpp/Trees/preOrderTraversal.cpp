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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> preOrder;
        stack<TreeNode*> st;
        while(root!=NULL || !st.empty()){
            while(root != NULL){
                preOrder.push_back(root->val);
                st.push(root);
                root = root->left;
            }
            root = st.top()->right;
            st.pop();
        }
        return preOrder;
    }
};