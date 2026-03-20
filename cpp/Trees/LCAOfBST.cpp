/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(root->val<p->val && root->val<q->val) return lowestCommonAncestor(root->right, p, q);
        if(root->val>p->val && root->val>q->val) return lowestCommonAncestor(root->left, p, q);
        return root;
    }
};

/*

This code is the **Binary Search Tree (BST)** version of the Lowest Common Ancestor (LCA) problem. It is much more efficient than the general binary tree version because it uses the BST property: **Left < Root < Right**.

Instead of searching the entire tree, this algorithm "descends" directly toward the nodes, making it very fast.

---

### Step-by-Step Logic

The core idea is to find the **"split point"**. The LCA is the first node we encounter where $p$ and $q$ are no longer in the same subtree.

#### 1. Both nodes are in the Right Subtree
```cpp
if(root->val < p->val && root->val < q->val) 
    return lowestCommonAncestor(root->right, p, q);
```
If the current `root` value is **smaller** than both $p$ and $q$, then both targets must be located somewhere in the right subtree. We ignore the left side entirely and move right.

#### 2. Both nodes are in the Left Subtree
```cpp
if(root->val > p->val && root->val > q->val) 
    return lowestCommonAncestor(root->left, p, q);
```
If the current `root` value is **larger** than both $p$ and $q$, then both targets must be in the left subtree. We move left.

#### 3. The Split Point (The LCA)
```cpp
return root;
```
If neither of the above conditions is true, it means one of three things:
* One node is in the left subtree and the other is in the right.
* The current node is equal to $p$.
* The current node is equal to $q$.

In all these cases, the current `root` is the **Lowest Common Ancestor**.

---

### Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(h)$ | We only visit one node at each level of the tree. In a balanced BST, this is $O(\log n)$. |
| **Space Complexity** | $O(h)$ | Due to the recursion stack. (This can be easily converted to $O(1)$ space using a simple `while` loop). |

---

### Why is this better than the general version?
In a general Binary Tree, you have to look at **every** node to be sure where $p$ and $q$ are. In a BST, the values act like a GPS, telling you exactly which branch to take.



### Bonus: The $O(1)$ Iterative Version
Since this is "tail recursion" (the recursive call is the last thing the function does), you can write it as a loop to save memory:

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (root->val < p->val && root->val < q->val)
            root = root->right;
        else if (root->val > p->val && root->val > q->val)
            root = root->left;
        else
            return root;
    }
    return nullptr;
}
```

Would you like me to explain how to handle a case where $p$ or $q$ might not actually exist in the tree?

*/

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (root->val < p->val && root->val < q->val)
            root = root->right;
        else if (root->val > p->val && root->val > q->val)
            root = root->left;
        else
            return root;
    }
    return nullptr;
} 