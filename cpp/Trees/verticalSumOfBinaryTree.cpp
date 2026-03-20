// C++ program to find Vertical Sum in a given Binary Tree

#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int x){
         data = x;
          left = right = nullptr;
    }
};

// Traverses the tree in in-order form and populates a hashMap that contains the vertical sum
void verticalSumUtil(Node *node, int hd, unordered_map<int, int> &mp, int &mn, int &mx) {
    // Base case
    if (node == nullptr) return;

    // Recur for left subtree
    verticalSumUtil(node->left, hd-1, mp, mn, mx);

    // Add val of current node to map entry of corresponding hd
    mp[hd] += node->data;
    mn = min(mn, hd);
      mx = max(mx, hd);
  
    // Recur for right subtree
    verticalSumUtil(node->right, hd+1, mp, mn, mx);
}

// Function to find vertical sum
vector<int> verticalSum(Node *root) {
  
    // a map to store sum of nodes for each horizontal distance
    unordered_map <int, int> mp;
    
      // mn is for storing the minimum hd
      // mx is for storing the maximum hd
      int mn = 0, mx = 0;
  
    // populate the map
    verticalSumUtil(root, 0, mp, mn, mx);
      vector<int> result;
  
    for(int i = mn; i <= mx; i++) {
         result.push_back(mp[i]); 
    }
      return result;
}

int main() {
  
    // Create binary tree as shown in above figure
      //        1
      //      /  \  
      //     2    3
      //    / \  / \
      //   4   5 6  7
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    vector<int> res = verticalSum(root);
    for(int i : res) {
          cout << i << " ";
    }
    return 0;
}

// Code 2

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> verticalSum(TreeNode* root) {
        if (!root) return {};

        // Map to store: <Horizontal Distance, Sum of nodes at that HD>
        map<int, int> hdMap;

        // Queue for Level Order Traversal: <Node, Horizontal Distance>
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            pair<TreeNode*, int> current = q.front();
            q.pop();

            TreeNode* node = current.first;
            int hd = current.second;

            // Add node value to the corresponding horizontal distance
            hdMap[hd] += node->val;

            // Process left child: HD decreases by 1
            if (node->left) {
                q.push({node->left, hd - 1});
            }

            // Process right child: HD increases by 1
            if (node->right) {
                q.push({node->right, hd + 1});
            }
        }

        // Extract values from map into a vector (map is already sorted by HD)
        vector<int> result;
        for (auto const& [hd, sum] : hdMap) {
            result.push_back(sum);
        }

        return result;
    }
};


/*

This code solves the **Vertical Sum** problem using an iterative **Breadth-First Search (BFS)** approach. The goal is to sum up all node values that fall on the same "vertical line."

### 1. The Core Concept: Horizontal Distance (HD)
To determine which vertical line a node belongs to, we use a coordinate system where the root is at **0**.
* Moving **left** decreases the distance by 1 ($HD - 1$).
* Moving **right** increases the distance by 1 ($HD + 1$).



---

### 2. Key Data Structures
The code uses three main tools to get the job done:
* **`queue<pair<TreeNode*, int>> q`**: This stores the current node and its calculated $HD$. Because it's a queue, the code processes the tree level-by-level (BFS).
* **`map<int, int> hdMap`**: This is an **Ordered Map**. It maps a specific $HD$ (like -2, 0, or 1) to the running sum of all nodes found at that distance. 
    * *Crucial Note:* A `std::map` automatically keeps its keys in ascending order. This means the leftmost vertical lines (negative numbers) will naturally appear before the rightmost ones.
* **`vector<int> result`**: The final container used to return just the sums, stripped of their $HD$ keys.

---

### 3. Step-by-Step Execution

#### The Traversal Loop
1.  **Initialization**: The root is pushed into the queue with an $HD$ of **0**.
2.  **Processing**: The code pulls the front node from the queue.
3.  **Summing**: It looks up the current $HD$ in `hdMap` and adds the node's value to whatever sum is already there: `hdMap[hd] += node->val;`.
4.  **Branching**:
    * If there's a **left child**, it's added to the queue with $hd - 1$.
    * If there's a **right child**, it's added to the queue with $hd + 1$.



#### The Final Extraction
Once the queue is empty, the `hdMap` looks something like this for a typical tree:
* `-1`: Sum of leftmost nodes
* ` 0`: Sum of center nodes
* ` 1`: Sum of rightmost nodes

The `for` loop iterates through the map. Because the map is sorted by key, it collects the sums from left to right and pushes them into the `result` vector.

---

### 4. Complexity Analysis
* **Time Complexity**: $O(N \log W)$, where $N$ is the total nodes and $W$ is the number of vertical lines (width). The $\log W$ factor comes from inserting/updating the `std::map`.
* **Space Complexity**: $O(N)$. In a worst-case scenario (a full tree), the queue will hold the most nodes at the bottom level (roughly $N/2$).

### Pro-Tip: Map vs. Unordered Map
If you used `unordered_map`, the code would run slightly faster ($O(N)$), but the vertical sums would be in a random order. You would then have to manually find the minimum and maximum $HD$ to sort them, which is why `std::map` is the "cleaner" choice here.

Would you like to see how to solve this same problem using **Recursion (DFS)** instead of a queue?

*/