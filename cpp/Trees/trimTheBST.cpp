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
    void trim(TreeNode *root, int low, int high){
        if(!root) return;
        while(root->left != NULL){
            if(root->left->val < low) root->left = root->left->right;
            else if(root->left->val > high) root->left = root->left->left;
            else break;
        }
        while(root->right != NULL){
            if(root->right->val < low) root->right = root->right->right;
            else if(root->right->val > high) root->right = root->right->left;
            else break;
        }
        trim(root->left, low, high);
        trim(root->right, low, high);
    }

    TreeNode* trimBST(TreeNode* root, int low, int high) {
        TreeNode *dummy = new TreeNode(-1);
        dummy->left = root;
        trim(dummy, low, high);
        return dummy->left;
    }
};


/*

This code is designed to **trim a Binary Search Tree (BST)** so that all remaining nodes have values within the range $[low, high]$. If a node's value falls outside this range, it is removed, and its appropriate subtree is "promoted" to take its place.

Here is a breakdown of how the logic works:

---

### 1. The Core Strategy: "Child Validation"
Unlike many recursive solutions that handle the *current* node, this specific implementation focuses on the **children** of the current node. 

The `trim` function acts as a parent looking at its immediate left and right children to see if they are valid. If a child is out of bounds, the parent "re-wires" its pointer to a valid grandchild.



### 2. The `trim` Helper Function
This function does the heavy lifting using two `while` loops:

* **The Left Child Loop:** It checks if `root->left` is out of bounds.
    * If `val < low`: The entire left subtree of that child is also too small. So, it replaces the left child with the child's **right** subtree.
    * If `val > high`: The entire right subtree of that child is too large. So, it replaces the left child with the child's **left** subtree.
    * It keeps looping until the `root->left` is either `NULL` or contains a value within $[low, high]$.
* **The Right Child Loop:** Performs the exact same logic for `root->right`.
* **Recursion:** Once the immediate children are "safe" (or null), it calls `trim` on them to fix the rest of the tree further down.

---

### 3. The `dummy` Node Trick
The `trimBST` function uses a common linked-list/tree technique: a **Dummy Node**.

```cpp
TreeNode *dummy = new TreeNode(-1);
dummy->left = root;
```

**Why is this here?**
If the original `root` of the tree needs to be deleted (e.g., the root is 10, but the range is $[15, 20]$), the `trim` function needs a "parent" to hold the pointer and change it. The dummy node acts as a permanent parent for the real root, allowing the code to swap out the root if necessary without crashing.

---

### Key Observations
* **BST Property:** This code relies on the fact that in a BST, all nodes to the left are smaller and all nodes to the right are larger. This is why it can safely "discard" a whole subtree and just keep the one that might still be in range.
* **Memory Note:** In a real-world scenario (or stricter C++ environments), you would want to `delete` the nodes that are being unlinked to prevent memory leaks. This code simply bypasses them by moving pointers.

---

### Summary Table
| Feature | Explanation |
| :--- | :--- |
| **Logic Type** | Top-down iterative checking within a recursive framework. |
| **Time Complexity** | $O(N)$, where $N$ is the number of nodes (each node is visited once). |
| **Space Complexity** | $O(H)$, where $H$ is the height of the tree (due to the recursion stack). |

Would you like me to show you the more "standard" recursive version of this algorithm to compare the two approaches?

*/


// Code 2

class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (!root) return nullptr;

        // Step 1: Find a valid root that is within [low, high]
        while (root && (root->val < low || root->val > high)) {
            if (root->val < low) {
                root = root->right; // Root is too small, try the right side
            } else {
                root = root->left;  // Root is too large, try the left side
            }
        }

        if (!root) return nullptr;

        // Step 2: Trim the left subtree
        TreeNode* current = root;
        while (current->left) {
            if (current->left->val < low) {
                // The left child is too small; its right child might be valid
                current->left = current->left->right;
            } else {
                // The left child is valid; move deeper to check its children
                current = current->left;
            }
        }

        // Step 3: Trim the right subtree
        current = root;
        while (current->right) {
            if (current->right->val > high) {
                // The right child is too large; its left child might be valid
                current->right = current->right->left;
            } else {
                // The right child is valid; move deeper
                current = current->right;
            }
        }

        return root;
    }
};

/*

This code provides an **iterative solution** to trim a Binary Search Tree (BST). It effectively "prunes" the branches that fall outside the range $[low, high]$ without using recursion, which makes it very memory-efficient.

Here is the step-by-step logic of how it works:

---

### Step 1: Finding the "True" Root
Before we can trim the branches, we need to make sure the **top** of the tree (the root) is actually valid. If the root is too small, we move to its right child; if it's too large, we move to its left.

```cpp
while (root && (root->val < low || root->val > high)) {
    if (root->val < low) root = root->right;
    else root = root->left;
}
```
* **Why?** In a BST, if a node is less than `low`, its entire left subtree is also less than `low`. We discard the node and its left side, then check the right side.
* Once this loop finishes, `root` is either `nullptr` (nothing in range) or a node that is **guaranteed** to be between `low` and `high`.

---

### Step 2: Trimming the Left Subtree
Now that we have a valid root, we walk down its left side.



```cpp
while (current->left) {
    if (current->left->val < low) {
        current->left = current->left->right; 
    } else {
        current = current->left;
    }
}
```
* We only check for `val < low` here. Why? Because we are on the left side of a root that we already know is $\le high$, so no node on this side can possibly be "too large."
* If a left child is too small, we "bypass" it by pointing the current node to that child's **right** child. We don't move `current` yet, because the new child needs to be checked too!

---

### Step 3: Trimming the Right Subtree
This is the mirror image of Step 2. We go back to the root and walk down the right side.

```cpp
while (current->right) {
    if (current->right->val > high) {
        current->right = current->right->left;
    } else {
        current = current->right;
    }
}
```
* We only check for `val > high`.
* If a node is too large, we bypass it by pointing to its **left** child.

---

### Why is this iterative approach good?

| Advantage | Explanation |
| :--- | :--- |
| **Space Efficiency** | It uses $O(1)$ extra space. Unlike recursion, it doesn't add frames to the call stack, preventing "Stack Overflow" on very deep trees. |
| **Predictability** | It follows a clear three-path logic: fix the head, fix the left arm, fix the right arm. |
| **Time Complexity** | $O(H)$, where $H$ is the height of the tree. In the worst case, you visit one path from root to leaf. |

### A Quick Warning
Just like the previous version, this code "unlinks" nodes but doesn't technically `delete` them from memory. In a competitive programming environment, this is fine, but in a real C++ application, you would need to manage the memory of the discarded nodes to avoid a **memory leak**.

Would you like me to add the `delete` logic to this code so it handles memory cleanup properly?

*/

// Code 3

class Solution {
public:
    // Helper to clean up memory for discarded subtrees
    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    TreeNode* trimBST(TreeNode* root, int low, int high) {
        // Step 1: Find the valid root and delete out-of-bounds nodes along the way
        while (root && (root->val < low || root->val > high)) {
            TreeNode* temp = root;
            if (root->val < low) {
                root = root->right;
                temp->right = nullptr; // Disconnect to avoid deleting the part we keep
            } else {
                root = root->left;
                temp->left = nullptr; 
            }
            deleteTree(temp); // Delete the node and its invalid branch
        }

        if (!root) return nullptr;

        // Step 2: Trim the left subtree
        TreeNode* current = root;
        while (current->left) {
            if (current->left->val < low) {
                TreeNode* toDelete = current->left;
                // Save the right child (which might be valid) before deleting
                current->left = current->left->right;
                toDelete->right = nullptr; 
                deleteTree(toDelete);
            } else {
                current = current->left;
            }
        }

        // Step 3: Trim the right subtree
        current = root;
        while (current->right) {
            if (current->right->val > high) {
                TreeNode* toDelete = current->right;
                // Save the left child before deleting
                current->right = current->right->left;
                toDelete->left = nullptr;
                deleteTree(toDelete);
            } else {
                current = current->right;
            }
        }

        return root;
    }
};


/*

This code is a "memory-safe" iterative version of a BST trimming algorithm. While many solutions simply move pointers and leave the old nodes floating in memory (memory leaks), this version explicitly cleans up the discarded nodes using a post-order traversal.

Here is the breakdown of the logic:

---

### 1. The Cleanup Specialist: `deleteTree`
This helper function is crucial for C++ memory management. It uses recursion to delete nodes from the bottom up.
* It visits the left child, then the right child, and **only then** deletes the current node.
* This ensures you don't lose the "address" of a child before you've had a chance to delete it.



---

### 2. Step 1: Finding the New "Head"
The first `while` loop finds the first node in the tree that actually falls within the $[low, high]$ range.
* **The "Snip":** Before moving the `root` pointer to a child, it stores the old root in `temp`.
* **The "Disconnect":** `temp->right = nullptr` (or `left`) is the most important line. It "cuts the cord" between the node we are throwing away and the part of the tree we want to keep.
* If we didn't disconnect them, calling `deleteTree(temp)` would accidentally wipe out the entire valid subtree attached to it!

---

### 3. Step 2 & 3: Pruning the Branches
Once the root is stable, the code traverses down the left and right spines.

* **Trimming Left (`val < low`):** If a left child is too small, its right child might still be valid (because right children are always larger). The parent adopts that grandchild, and the "too small" child is deleted.
* **Trimming Right (`val > high`):** If a right child is too large, its left child might still be valid. The parent adopts the left grandchild, and the "too large" child is deleted.



---

### Why this code is "Robust"
| Feature | Benefit |
| :--- | :--- |
| **Iterative Main Logic** | Prevents $O(N)$ stack depth, avoiding stack overflow on deep, skewed trees. |
| **Manual `delete`** | Prevents memory leaks, which is vital for long-running applications or large datasets. |
| **Post-Order Deletion** | Safely clears entire subtrees that fall outside the range in one go. |

---

### A Logic Visualization
Imagine a node **7** with a left child **3**, and our `low` is **5**.
1. The code sees `current->left->val` (3) is less than 5.
2. It looks at 3's right child (maybe it's 4.5). 
3. It makes **7** point directly to **4.5**.
4. It sets **3**'s right pointer to `null` so 4.5 isn't deleted.
5. It calls `deleteTree` on **3** (and its left subtree, which must also be $< 5$).

**Would you like me to explain how this could be modernized even further using C++ Smart Pointers (`std::unique_ptr`), which would remove the need for the `deleteTree` function entirely?**

*/


/*

This specific function is a recursive **destructor** for a binary tree. Its sole purpose is to clear a tree from memory, node by node, to prevent a **memory leak**.

In C++, when you create nodes using `new`, they stay in a part of memory called the **heap** until you explicitly `delete` them. Because a tree is a collection of connected nodes, you can't just delete the root; you have to delete every single child node as well.

---

### How the Logic Works (Post-Order Traversal)
The function uses a strategy called **Post-Order Traversal**. This means it visits children *before* it visits the parent. If you deleted the parent first, you would lose the pointers (the "addresses") to the children, and they would be stuck in memory forever.



Here is the step-by-step execution for a single node:

1.  **Base Case (`if (!node) return;`):** If the function reaches a null pointer (the end of a branch), it simply stops and goes back up.
2.  **Left Recursion (`deleteTree(node->left);`):** It dives all the way down to the leftmost leaf.
3.  **Right Recursion (`deleteTree(node->right);`):** It then checks the right child of the current subtree.
4.  **The Deletion (`delete node;`):** Only after both the left and right subtrees are confirmed to be deleted (or null) does it finally delete the current node.

---

### A Trace Example
Imagine a small tree where **A** is the parent of **B** (left) and **C** (right):

* Call `deleteTree(A)`
    * Calls `deleteTree(B)`
        * B has no children, so it finishes the left/right recursions and **deletes B**.
    * Back to A, calls `deleteTree(C)`
        * C has no children, so it finishes the left/right recursions and **deletes C**.
    * Finally, both children of A are gone, so it **deletes A**.



### Why is this necessary?
If you are writing a "Trim BST" algorithm or any program that modifies a tree, you often "disconnect" entire branches. Without this function, those disconnected branches would continue to consume RAM even though your program can no longer "see" them.

**Would you like to see how we could write this same function using a "Smart Pointer" (like `std::unique_ptr`) so that C++ handles the deletion automatically?**

*/