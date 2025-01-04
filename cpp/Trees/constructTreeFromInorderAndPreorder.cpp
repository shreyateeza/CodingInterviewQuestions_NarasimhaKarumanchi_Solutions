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
    TreeNode* buildTreeUtil(vector<int>& preorder, vector<int>& inorder, int start, int end, int& position){
        if(start > end) return NULL;
        TreeNode* node = new TreeNode(preorder[position]);
        int idx = -1;
        for(int i=start; i<=end; i++){
            if(inorder[i] == preorder[position]){
                idx = i;
                break;
            }
        }
        position++;
        node->left = buildTreeUtil(preorder, inorder, start, idx-1, position);
        node->right = buildTreeUtil(preorder, inorder, idx+1, end, position);
        return node;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int position = 0, N = preorder.size();
        return buildTreeUtil(preorder, inorder, 0, N-1, position);        
    }
};