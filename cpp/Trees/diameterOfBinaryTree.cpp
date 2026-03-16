// C++ program to find the diameter of a binary tree.
#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// Recursive function which finds the height of root and also calculates the diameter of the tree.
int diameterRecur(Node* root, int &ans) {
  
    // Base case: tree is empty
    if (root == nullptr)
        return 0;
    
    // find the height of left and right subtree (it will also find of diameter for left and right subtree).
    int lHeight = diameterRecur(root->left, ans);
    int rHeight = diameterRecur(root->right, ans);
    
    // Check if diameter of root is greater than ans.
    ans = max(ans, lHeight+rHeight);
    
    // return the height of current subtree.
    return 1 + max(lHeight, rHeight);
}

// Function to get diameter of a binary tree
int diameter(Node* root) {
  
    int ans = 0;
    
    diameterRecur(root, ans);
    
    return ans;
}

int main() {

    // Constructed binary tree is
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    cout << diameter(root) << endl;

    return 0;
}

/*

This code calculates the **Diameter of a Binary Tree**, which is defined as the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The beauty of this specific implementation is its efficiency: it calculates both the **height** and the **diameter** in a single pass.

---

### 1. The Core Logic: How it Works

The diameter of a tree at any given node is the sum of the heights of its left and right subtrees.

The function `diameterRecur` performs a Post-order Traversal (Left, Right, Root):

1. **Go Deep:** It travels down to the leaf nodes first.
2. **Calculate Height:** As it returns (backtracks) up the tree, it calculates the height of the current node:

$$Height = 1 + \max(leftHeight, rightHeight)$$


3. **Update Diameter:** At every single node, it imagines that node is the "highest point" of a path. It calculates the path length ($leftHeight + rightHeight$) and updates the global maximum (`ans`) if this path is the longest found so far.

---

### 2. Code Breakdown

#### The "Two-in-One" Recursive Function

```cpp
int diameterRecur(Node* root, int &ans) {
    if (root == nullptr) return 0; // Base case: height of nothing is 0

    int lHeight = diameterRecur(root->left, ans);
    int rHeight = diameterRecur(root->right, ans);

    // Update the diameter: the path through the current node
    ans = max(ans, lHeight + rHeight);

    // Return height to the parent node
    return 1 + max(lHeight, rHeight);
}

```

* **`int &ans`**: This is a **reference parameter**. It acts like a global variable that keeps track of the "Best Diameter Seen So Far" across all recursive calls.
* **The Return Value**: Even though the function is helping find the diameter, it returns the **height**. This allows the parent node to know how deep its subtrees go.

---

### 3. Complexity Analysis

#### Time Complexity: $O(N)$

* The algorithm visits every node exactly once.
* At each node, it performs constant time operations (addition and `max`).
* Unlike the "naive" approach (which calls a separate height function inside the diameter function, resulting in $O(N^2)$), this version is perfectly linear.

#### Space Complexity: $O(H)$

* $H$ is the height of the tree.
* This space is used by the **recursion stack**.
* In the worst case (a skewed tree like a linked list), this is $O(N)$. In a balanced tree, it is $O(\log N)$.

---

### 4. Example Trace

Using the tree in the `main()` function:

```
      1
     / \
    2   3
   / \
  4   5

```

1. Nodes **4** and **5** return height `1` to Node **2**.
2. At Node **2**:
* `lHeight = 1`, `rHeight = 1`.
* `ans` becomes $\max(0, 1+1) = \mathbf{2}$.
* Node **2** returns height $1 + \max(1, 1) = \mathbf{2}$ to Node **1**.


3. Node **3** returns height `1` to Node **1**.
4. At Node **1**:
* `lHeight = 2`, `rHeight = 1`.
* `ans` becomes $\max(2, 2+1) = \mathbf{3}$.
* Final diameter is **3** (The path could be 4 -> 2 -> 1 -> 3).



Would you like me to show you how to modify this code to return the actual path (the nodes themselves) instead of just the length?

*/

// Code 2

#include <iostream>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

int iterativeDiameter(Node* root) {
    if (!root) return 0;

    stack<Node*> s;
    // Map to store height of each node: map[node] = height
    unordered_map<Node*, int> heightMap;
    int maxDiameter = 0;

    s.push(root);

    while (!s.empty()) {
        Node* curr = s.top();

        // If node is leaf or its children are already processed (present in map)
        bool leftDone = !curr->left || heightMap.count(curr->left);
        bool rightDone = !curr->right || heightMap.count(curr->right);

        if (leftDone && rightDone) {
            s.pop();

            int lh = curr->left ? heightMap[curr->left] : 0;
            int rh = curr->right ? heightMap[curr->right] : 0;

            // Update global diameter
            maxDiameter = max(maxDiameter, lh + rh);

            // Store height of current node
            heightMap[curr] = 1 + max(lh, rh);
        } else {
            // Push children to stack (Right then Left to process Left first)
            if (curr->right && !heightMap.count(curr->right)) s.push(curr->right);
            if (curr->left && !heightMap.count(curr->left)) s.push(curr->left);
        }
    }

    return maxDiameter;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Diameter: " << iterativeDiameter(root) << endl;
    return 0;
}

/*

This code finds the **Diameter** of a Binary Tree using an **iterative** approach. The diameter is the longest path between any two nodes, which essentially boils down to finding the node where the sum of its left subtree height and right subtree height is maximized.

To do this iteratively, the code simulates a **Post-order Traversal** (Left $\rightarrow$ Right $\rightarrow$ Root) because a parent's height can only be calculated *after* the heights of its children are known.

---

### ## 1. Key Components

* **`stack<Node*> s`**: Used to simulate the recursion stack. It keeps track of the nodes we are currently visiting.
* **`unordered_map<Node*, int> heightMap`**: This is the "memory" of the algorithm. It stores the calculated height of each node so that when we return to a parent, we can instantly look up the heights of its children.
* **Post-order Logic**: A node is only "popped" and processed if its children are either `NULL` or have already had their heights stored in the `heightMap`.

---

### ## 2. How the Logic Flows

#### **The Discovery Phase**

The code pushes nodes onto the stack. By pushing the **Right** child first and then the **Left** child, it ensures that the Left child is at the top of the stack and processed first.

#### **The Processing Phase**

When the code reaches a leaf node (or a node whose children are already in the `heightMap`), it performs these steps:

1. **Pop** the node from the stack.
2. **Retrieve Heights**: It gets `lh` (left height) and `rh` (right height) from the map.
3. **Calculate Diameter**: The path passing through this node is $lh + rh$. If this is larger than the previous `maxDiameter`, it updates it.
4. **Calculate Height**: It calculates its own height as $1 + \max(lh, rh)$ and saves it in the `heightMap` for its parent to use.

---

### ## 3. Complexity Analysis

| Type | Complexity | Explanation |
| --- | --- | --- |
| **Time** | **$O(N)$** | Each node is pushed and popped from the stack once. Map lookups are $O(1)$ on average. |
| **Space** | **$O(N)$** | We use a map to store the height of every single node in the tree. |

---

### ## 4. Example Trace

For a tree where `1` is the root, `2` is left, and `3` is right:

1. Stack: `[1]`.
2. Stack: `[1, 3, 2]`.
3. `2` is a leaf. `lh=0, rh=0`. `maxDiameter = 0`. `heightMap[2] = 1`. Pop `2`.
4. `3` is a leaf. `lh=0, rh=0`. `maxDiameter = 0`. `heightMap[3] = 1`. Pop `3`.
5. Back at `1`. Children `2` and `3` are in map.
6. `lh=1, rh=1`. `maxDiameter = 1 + 1 = 2`. `heightMap[1] = 2`. Pop `1`.
7. Return `2`.

---

**Would you like me to show you how to optimize the space complexity by removing the `unordered_map`?**

*/