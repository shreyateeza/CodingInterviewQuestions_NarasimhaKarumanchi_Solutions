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


/*

This code performs an **Iterative In-order Traversal** of a Binary Tree. While the recursive version is usually just three lines, this version uses an **explicit stack** to mimic the call stack, following the rule: **Left → Root → Right**.

---

### Step-by-Step Logic

The algorithm uses a `while` loop and a stack to keep track of nodes we need to revisit.

1.  **The "Dive Left" Phase:** The inner `while(root != NULL)` loop pushes the current node onto the stack and moves to the left child. It keeps doing this until it hits the "bottom-left" of the current subtree. This ensures we process the leftmost (smallest in a BST) elements first.
    

2.  **The "Visit" Phase:** Once we hit a `NULL` (the end of the left path), we pop the top node from the stack (`st.top()`). This node is our current "Root" in the L-Root-R sequence. We add its value to our `inOrder` vector.

3.  **The "Move Right" Phase:** After visiting the node, we move to `root = temp->right`. 
    * If a right child exists, the loop starts over, and we "Dive Left" into that new subtree. 
    * If no right child exists, the inner loop is skipped, and we pop the next parent from the stack.

---

### Why the `while` condition is `root != NULL || !st.empty()`?
* `root != NULL`: We use this to keep going when we move to a right child that might have its own subtree.
* `!st.empty()`: We use this to keep going when we've hit a leaf node and need to "backtrack" up to the parent.

---

### Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(n)$ | Every node is pushed onto and popped from the stack exactly once. |
| **Space Complexity** | $O(h)$ | The stack stores at most $h$ nodes, where $h$ is the height of the tree. In a balanced tree, this is $O(\log n)$; in a skewed tree, it's $O(n)$. |

---

### A Quick Trace Example
Imagine a tree: `[1, null, 2, 3]` (1 is root, 2 is right child, 3 is left child of 2).

1.  **Push 1**, move to `left` (NULL).
2.  **Pop 1**, add `1` to vector, move to `right` (Node 2).
3.  **Push 2**, move to `left` (Node 3).
4.  **Push 3**, move to `left` (NULL).
5.  **Pop 3**, add `3` to vector, move to `right` (NULL).
6.  **Pop 2**, add `2` to vector, move to `right` (NULL).
7.  Stack empty and root is NULL $\rightarrow$ **Done.**
8.  **Result:** `[1, 3, 2]`

Would you like to see how this compares to the **Morris Traversal**, which does this in $O(1)$ space?

*/

// Code 2 - Morris In-order Traversal C++ Code

#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    std::vector<int> morrisInorder(TreeNode* root) {
        std::vector<int> result;
        TreeNode* curr = root;

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // Case 1: No left child, visit this node and move right
                result.push_back(curr->val);
                curr = curr->right;
            } else {
                // Case 2: There is a left child, find the inorder predecessor
                TreeNode* prev = curr->left;
                while (prev->right != nullptr && prev->right != curr) {
                    prev = prev->right;
                }

                if (prev->right == nullptr) {
                    // Create a temporary thread to the current node
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    // Thread already exists; visit node and cut the thread
                    prev->right = nullptr;
                    result.push_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        return result;
    }
};

/*

The genius of the **Morris Traversal** is that it solves the "Where do I go next?" problem without using a stack or recursion. It does this by temporarily modifying the tree to create **"threads"**—pointers that lead back to the parent node.

Here is a breakdown of how this code works:

---

### 1. The Core Strategy: Finding the Predecessor
In an In-order traversal (Left-Root-Right), the node visited immediately before `curr` is its **In-order Predecessor** (the rightmost node in `curr`'s left subtree).

The code constantly looks for this predecessor to decide its next move.

### 2. The Logic Flow

#### Case 1: No Left Child (`curr->left == nullptr`)
If there is no left subtree, there's nothing to do on the left.
* **Action:** Record `curr->val` and move to the **right** child.

#### Case 2: Left Child Exists
If there is a left subtree, we find the **In-order Predecessor** (`prev`):
* **Sub-case A: First time visiting this subtree (`prev->right == nullptr`)**
    * We create a "thread" by setting `prev->right = curr`. 
    * This is like leaving a breadcrumb. It allows us to return to `curr` after finishing the left side.
    * **Action:** Move to `curr->left`.
    


* **Sub-case B: Returning from the left subtree (`prev->right == curr`)**
    * If the predecessor’s right pointer already points to `curr`, it means we’ve already finished the left subtree and followed our breadcrumb back up.
    * **Action:** Clean up! Set `prev->right = nullptr` (restore the tree), record `curr->val`, and move to `curr->right`.

---

### Complexity Analysis

| Metric | Complexity | Why? |
| :--- | :--- | :--- |
| **Time Complexity** | $O(n)$ | Each edge in the tree is traversed at most 3 times (finding the predecessor, creating the thread, and removing it). |
| **Space Complexity** | **$O(1)$** | This is the main selling point. No stack or recursion is used; we only use two pointers (`curr` and `prev`). |

---

### Why use this over a Stack?
* **Memory Efficiency:** If you are working on a system with very limited memory, or if the tree is extremely deep (causing a stack overflow), Morris is the only way to go.
* **Destructive (Temporarily):** The only downside is that the tree is briefly modified during the process. If another thread tries to read the tree while Morris is running, it will see a corrupted structure.

### Quick Summary of the "Thread"
1.  **Go Left:** But first, link the bottom-right of the left subtree back to the current node.
2.  **Come Back:** Use that link to return to the current node.
3.  **Go Right:** Cut the link and move to the right subtree.

Would you like to see how to modify this code for **Pre-order** traversal? (It only involves moving the `result.push_back` line!)

*/