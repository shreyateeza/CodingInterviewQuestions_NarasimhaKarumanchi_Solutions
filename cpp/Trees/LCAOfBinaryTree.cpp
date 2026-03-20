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
        if(!root || root==p || root==q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if(!left) return right;
        if(!right) return left;
        return root;        
    }
};

/*

This is the classic recursive solution for finding the **Lowest Common Ancestor (LCA)** of two nodes in a Binary Tree. The LCA is defined as the deepest node in the tree that has both `p` and `q` as descendants.

Think of this code as a "bottom-up" search where each node reports back to its parent whether it found `p`, `q`, or both.

---

### Step-by-Step Logic

#### 1. The Base Cases
```cpp
if(!root || root==p || root==q) return root;
```
As the recursion goes down, it stops and returns the current node if:
* It hits `nullptr` (reached the end of a branch).
* It finds node `p`.
* It finds node `q`.

#### 2. The Recursive "Ask"
```cpp
TreeNode *left = lowestCommonAncestor(root->left, p, q);
TreeNode *right = lowestCommonAncestor(root->right, p, q);
```
The current node asks its **left child** and **right child**: *"Hey, did you find p or q in your subtrees?"*

#### 3. The Decision Logic (The "Merge")
Once the children report back, the node decides what to return to its own parent:

* **If `left` is NULL:** This means neither `p` nor `q` were found in the left subtree. Therefore, whatever was found on the `right` (even if it's NULL) is our best lead.
* **If `right` is NULL:** Similarly, if the right side is empty, we return whatever the `left` side found.
* **If both `left` and `right` are NOT NULL:** This is the "Eureka!" moment. It means `p` was found in one subtree and `q` was found in the other. Since this is the first (lowest) node where this happens, **this current node is the LCA.**

---

### Visualization of the Logic


Imagine searching for nodes **4** and **5**:
1.  A node sees **4** on its left and **5** on its right.
2.  It returns **itself** to the caller.
3.  Higher nodes will see one side returning a value and the other returning `NULL`, so they will just keep passing that LCA value up the tree.

---

### Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(n)$ | In the worst case, we might visit every node in the tree once. |
| **Space Complexity** | $O(h)$ | The maximum depth of the recursion stack is equal to the height of the tree ($h$). For a balanced tree, this is $O(\log n)$. |

---

### Key Takeaway
This code works for a **general Binary Tree**. If this were a **Binary Search Tree (BST)**, we could make it much faster by using the property that values to the left are smaller and values to the right are larger, allowing us to skip entire subtrees.

Would you like to see how much simpler the **BST version** of this algorithm looks?

*/

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        if(!p || !q) return nullptr;
        // Map to store parent pointers: key = child, value = parent
        unordered_map<TreeNode*, TreeNode*> parentMap;
        stack<TreeNode*> st;

        parentMap[root] = nullptr;
        st.push(root);

        // 1. Traverse the tree until we have found both p and q
        while (parentMap.find(p) == parentMap.end() || parentMap.find(q) == parentMap.end()) {
            TreeNode* curr = st.top();
            st.pop();

            if (curr->left) {
                parentMap[curr->left] = curr;
                st.push(curr->left);
            }
            if (curr->right) {
                parentMap[curr->right] = curr;
                st.push(curr->right);
            }
        }

        // 2. Build a set of all ancestors for node p
        unordered_set<TreeNode*> ancestorsP;
        while (p != nullptr) {
            ancestorsP.insert(p);
            p = parentMap[p]; // Move up to the parent
        }

        // 3. Move up from q; the first ancestor of q that is also in p's set is the LCA
        while (ancestorsP.find(q) == ancestorsP.end()) {
            q = parentMap[q];
        }

        return q;
    }
};

/*

This iterative solution for finding the **Lowest Common Ancestor (LCA)** in a general Binary Tree is a "breadcrumb" approach. Instead of using recursion to backtrack, it builds a map of the entire family tree until it finds the nodes in question, then compares their "bloodlines" (paths to the root) to find where they first meet.

Here is the logic broken down into three clear phases:

---

### Phase 1: Build the Family Tree (`parentMap`)
In a standard Binary Tree, nodes only know who their children are—they have no idea who their parent is. This code fixes that.
* **The Goal:** Populate `parentMap` such that `parentMap[child] = parent`.
* **The Process:** It performs a simple **Pre-order traversal** using a stack. 
* **The Stop Condition:** The `while` loop runs only until both `p` and `q` are found in the map. Once we know the parents of both targets, we have enough information to stop traversing.



### Phase 2: Trace $p$'s Path to the Root
Now that we have the `parentMap`, we can treat the tree like a linked list moving **upward**.
* It takes node `p` and moves to `parentMap[p]`, then the parent of that, and so on.
* Every node on this path is stored in an `unordered_set` called `ancestorsP`.
* This set now contains every single ancestor of $p$, all the way up to the `root`.

### Phase 3: Trace $q$'s Path and Intersect
Finally, we do the same for node `q`, but we check for a match along the way.
* We move up from `q` node by node.
* For each ancestor of `q`, we ask: *"Is this node also in $p$'s ancestor set?"*
* The **first** node we find that exists in both paths must be the **Lowest Common Ancestor**.



---

### Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(N)$ | In the worst case, we might visit every node in the tree to find $p$ and $q$. The path tracing takes $O(H)$ (height). |
| **Space Complexity** | $O(N)$ | The `parentMap` stores entries for nodes. Even if we stop early, in a skewed tree, this can grow to $O(N)$. |

### Pros and Cons vs. Recursion

* **Pro:** It is **Iterative**. It won't crash with a `StackOverflowError` if you have a tree with 100,000 nodes in a single line (skewed tree).
* **Con:** It uses **More Memory**. The recursive version uses $O(H)$ space (height of the tree), while this iterative version uses $O(N)$ space because of the `unordered_map`.

---

### A Quick Reality Check
One small detail: this code assumes that both $p$ and $q$ **definitely exist** in the tree. If one were missing, the `while` loop in Phase 1 would run through the entire tree and eventually finish, but Phase 2 or 3 might encounter issues.

Would you like to see how to solve this using **only two pointers** (similar to finding the intersection of two linked lists) to save a bit of set-processing time?

*/