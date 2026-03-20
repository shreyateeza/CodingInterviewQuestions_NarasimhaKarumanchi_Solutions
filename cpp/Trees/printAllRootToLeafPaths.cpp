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

/*

This code uses **Recursion** and **Backtracking** (technically "pass-by-value" backtracking) to find every possible path from the **root** of a binary tree to its **leaf nodes**.

Think of it as an explorer who leaves a trail of breadcrumbs. Every time they hit a dead end (a leaf), they write down the full path they took.

---

### Step-by-Step Logic

#### 1. The Entry Point (`binaryTreePaths`)
This is the "starter" function. It initializes an empty list for the final results (`result`) and an empty string (`temp`) to build the current path. It then kicks off the recursive helper.

#### 2. The Leaf Case (The "Base Case")
```cpp
if(!root->left && !root->right){
    string x = to_string(root->val);
    temp += x;
    result.push_back(temp);
    return;
}
```
When the function reaches a leaf node (a node with no children):
* It appends the current node's value to the path string.
* It **saves** that completed string into the `result` vector.
* It stops exploring that specific branch.

#### 3. The Recursive Exploration
```cpp
string x = to_string(root->val) + "->";
temp += x;
binaryTreePathsHelper(root->left, temp, result);
binaryTreePathsHelper(root->right, temp, result);
```
If the node is *not* a leaf:
* It appends the current value plus the arrow separator `"->"` to the path.
* It then calls itself for the **left child** and then the **right child**.



---

### A Crucial Detail: String Copying
Notice that `temp` is passed **by value** (not by reference like `&result`). 
* Every time the function calls itself, it creates a **new copy** of the `temp` string. 
* This is a clever way to handle backtracking. When the "Left" call finishes and the code moves to the "Right" call, the `temp` string for the Right call hasn't been modified by the Left call. It still looks exactly like it did when it arrived at the parent.

---

### Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(N^2)$ or $O(N \cdot H)$ | We visit every node once ($N$), but at each node, we create a copy of the path string. In a skewed tree, string copying can take $O(N)$ time, leading to $O(N^2)$. |
| **Space Complexity** | $O(N^2)$ or $O(N \cdot H)$ | Due to the recursion stack and the fact that we store many copies of strings of varying lengths across the recursion depth. |

---

### Comparison: Efficiency Tip
While this code is very readable, passing strings by value is memory-intensive. In a high-performance scenario, you would pass `temp` by **reference**, `push_back` the value, and then manually `pop_back` (remove) the value after the recursive calls are done.

Would you like to see the **optimized version** that uses a single string and manual backtracking to save memory?

*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (!root) return result;

        // Stack stores a pair: {Current Node, Path string up to this node}
        stack<pair<TreeNode*, string>> st;
        st.push({root, to_string(root->val)});

        while (!st.empty()) {
            pair<TreeNode*, string> curr = st.top();
            st.pop();

            TreeNode* node = curr.first;
            string path = curr.second;

            // If we hit a leaf node, add the accumulated path to our results
            if (!node->left && !node->right) {
                result.push_back(path);
            }

            // Push right child first so that left child is processed first (standard DFS)
            if (node->right) {
                st.push({node->right, path + "->" + to_string(node->right->val)});
            }
            if (node->left) {
                st.push({node->left, path + "->" + to_string(node->left->val)});
            }
        }

        return result;
    }
};

/*

This code implements an **Iterative Depth-First Search (DFS)** to find all paths from the root of a binary tree to its leaves. Since a typical stack only remembers which node to visit next, this code uses a **`std::pair`** to carry a "memory" of the path string alongside each node.

---

### The Three Main Components

#### 1. The "Memory" Stack
```cpp
stack<pair<TreeNode*, string>> st;
st.push({root, to_string(root->val)});
```
Instead of a simple stack of nodes, this uses a pair. 
* **`first`**: The pointer to the current `TreeNode`.
* **`second`**: The actual string representing the path taken from the root to reach this specific node. 
By bundling them together, each node "knows" exactly how it was reached.

#### 2. Leaf Detection (The Goal)
```cpp
if (!node->left && !node->right) {
    result.push_back(path);
}
```
As we pop elements from the stack, we check if the node is a **leaf** (no left or right child). If it is, we've completed a full path from root to leaf, so we add the accumulated `path` string to our final `result` vector.

#### 3. Exploration (The DFS Order)
```cpp
if (node->right) st.push({node->right, path + "->" + ...});
if (node->left)  st.push({node->left, path + "->" + ...});
```
We push the children onto the stack to keep the search going. 
* **The "Trick":** We push the **right** child first and the **left** child second. Because a stack is "Last-In, First-Out" (LIFO), this ensures the **left** child is popped and processed first, mimicking a standard recursive pre-order traversal.



---

### Why use `std::pair`?
In recursion, the path is stored in the function's call stack. In an iterative approach, we don't have that automatic storage. By pushing the path string onto the stack with the node, we ensure that when we branch off (e.g., from a parent to its right child), we aren't accidentally including nodes from the left branch in our string.

---

### Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(N \cdot H)$ | We visit every node ($N$). However, at each node, we perform string concatenation. In the worst case (a skewed tree), the path string length is $H$ (height), leading to $O(N \cdot H)$. |
| **Space Complexity** | $O(N \cdot H)$ | The stack can hold up to $N$ pairs in a skewed tree. Each pair contains a string that can be up to $H$ characters long. |

---

### Summary of Logic
1.  **Start** at the root with its value as the initial string.
2.  **Pop** a node and its path.
3.  **If it's a leaf**, save the path.
4.  **If it has children**, create new path strings for them (Current Path + `->` + Child Value) and push them onto the stack.
5.  **Repeat** until the stack is empty.

Would you like to see how this same logic can be implemented using a **Queue (BFS)**, which would find the paths level-by-level instead of branch-by-branch?

*/