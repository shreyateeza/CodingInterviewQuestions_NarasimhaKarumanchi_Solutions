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

    int successor(TreeNode *root) {
        root = root->right;
        while (root->left != NULL) root = root->left;
        return root->val;
    }

    int predecessor(TreeNode *root) {
        root = root->left;
        while (root->right != NULL) root = root->right;
        return root->val;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) return NULL;
        if (key > root->val) root->right = deleteNode(root->right, key);
        else if (key < root->val) root->left = deleteNode(root->left, key);
        else {
            if (root->left == NULL && root->right == NULL) root = NULL;
            else if (root->right != NULL) {
                root->val = successor(root);
                root->right = deleteNode(root->right, root->val);
            }
            else {
                root->val = predecessor(root);
                root->left = deleteNode(root->left, root->val);
            }
        }
        return root;
        
    }
};


// Code 2

#include <iostream>

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* deleteNode(Node* root, int key) {
    Node* curr = root;
    Node* parent = nullptr;

    // 1. Locate the node to be deleted and its parent
    while (curr != nullptr && curr->data != key) {
        parent = curr;
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    // If key not found
    if (curr == nullptr) return root;

    // 2. Case: Node has 0 or 1 child
    if (curr->left == nullptr || curr->right == nullptr) {
        Node* newCurr;

        if (curr->left == nullptr)
            newCurr = curr->right;
        else
            newCurr = curr->left;

        // If deleting the root node
        if (parent == nullptr) return newCurr;

        // Re-attach parent to the new child
        if (curr == parent->left)
            parent->left = newCurr;
        else
            parent->right = newCurr;

        delete curr;
    } 
    // 3. Case: Node has 2 children
    else {
        Node* p_successor = nullptr;
        Node* successor = curr->right;

        // Find the in-order successor (leftmost in right subtree)
        while (successor->left != nullptr) {
            p_successor = successor;
            successor = successor->left;
        }

        // Replace current node's data with successor's data
        curr->data = successor->data;

        // Delete the successor node
        if (p_successor != nullptr)
            p_successor->left = successor->right;
        else
            curr->right = successor->right;

        delete successor;
    }

    return root;
}

/*

This iterative approach is the "road trip" version of BST deletion—instead of letting the recursion stack handle the path back up the tree, you manually keep track of the **parent** node so you can patch the holes once a node is removed.

Here is the step-by-step breakdown:

---

### 1. The Search Phase
The `while` loop traverses the tree starting from the `root`. 
* It updates `parent = curr` before moving to the next child.
* If `curr` becomes `nullptr`, the key doesn't exist, and the function exits.

### 2. Case: 0 or 1 Child
If the node to be deleted (`curr`) has at most one child:
1.  **Identify the replacement:** We pick the existing child (or `nullptr` if it's a leaf) and store it in `newCurr`.
2.  **Handle the Root:** If `parent` is `nullptr`, we are deleting the root, so `newCurr` becomes the new head of the tree.
3.  **Re-linking:** We check if `curr` was the left or right child of its parent and point that parent's pointer to `newCurr`.



### 3. Case: 2 Children
This is the trickiest part. You can't just delete a node with two children without breaking the tree structure.
1.  **Find Successor:** We go one step to the `right`, then as far `left` as possible. This finds the **In-order Successor** (the smallest value larger than the target).
2.  **Value Swap:** We copy the successor's data into our target node.
3.  **Delete Successor:** The successor is guaranteed to have **at most one child** (a right child). We bypass it by linking its parent to its right child and then `delete` the successor.



---

### Complexity Analysis

Let $h$ be the height of the BST and $n$ be the number of nodes.

| Complexity | Rating | Why? |
| :--- | :--- | :--- |
| **Time Complexity** | $O(h)$ | We traverse from root to leaf at most twice (once to find the node, once to find the successor). In a balanced tree, this is $O(\log n)$. In a skewed tree, it's $O(n)$. |
| **Space Complexity** | $O(1)$ | Unlike recursion, which uses $O(h)$ stack space, this uses only a fixed number of pointers (`curr`, `parent`, `successor`) regardless of tree size. |

---

### Key Comparison: Iterative vs. Recursive
The main advantage here is the **Space Complexity**. If you have a very deep, unbalanced tree (like a linked list), a recursive function might cause a **Stack Overflow**. This iterative version is "safe" because it keeps everything on the heap and uses constant auxiliary memory.

Would you like me to show you how to handle the "In-order Predecessor" (largest in the left subtree) as an alternative to the successor?

*/