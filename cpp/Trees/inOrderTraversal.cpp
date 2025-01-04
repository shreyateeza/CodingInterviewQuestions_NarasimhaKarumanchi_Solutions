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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inOrder;
        stack<TreeNode*> st;
        while(root!=NULL || !st.empty()){
            while(root != NULL){
                st.push(root);
                root = root->left;
            }
            TreeNode* temp = st.top();
            st.pop();
            inOrder.push_back(temp->val);
            root = temp->right;
        }
        return inOrder;
    }
};