#include<bits/stdc++.h>
using namespace std;

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
   int data;
   struct node* left;
   struct node* right;
};

/* If target is present in tree, then prints the ancestors
   and returns true, otherwise returns false. */
bool printAncestors(struct node *root, int target)
{
    stack<node*> st;
    while (root || !st.empty()) {
        while (root && root->data != target) {
            st.push(root);
            root = root->left;
        }
        
        if (root && root->data == target)
            break;
        
        if (!st.empty() && st.top()->right == NULL) {
            root = st.top();
            st.pop();
            
            while (!st.empty() && st.top()->right == root) {
                root = st.top();
                st.pop();
            }
        }
        
        root = (!st.empty()) ? st.top()->right : NULL;
    }
    
    if (!st.empty()) {
        while (!st.empty()) {
            cout << st.top()->data << " ";
            st.pop();
        }
        return true;
    }
    
    return false;
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newnode(int data)
{
  struct node* node = (struct node*)malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return(node);
}

/* Driver program to test above functions*/
int main()
{
  /* Construct the following binary tree
              1
            /   \
          2      3
        /  \
      4     5
     /
    7
  */
  struct node *root = newnode(1);
  root->left = newnode(2);
  root->right = newnode(3);
  root->left->left = newnode(4);
  root->left->right = newnode(5);
  root->left->left->left = newnode(7);

  printAncestors(root, 7);

  return 0;
}

/*

This C++ code is designed to find and print the **ancestors** of a specific target node in a binary tree. While many solutions for this problem use recursion, this specific implementation uses an **iterative approach with a stack**.

Think of the stack as a breadcrumb trail: as the code searches for the target, it keeps track of the path it took from the root.

---

## 1. The Core Logic: `printAncestors`
This function is the "meat" of the code. It performs a modified version of a **Post-order Traversal**.

### The Search Phase
1.  **Going Left:** It continuously pushes nodes onto the stack and moves to the `left` child until it either hits the `target` or a `NULL` leaf.
2.  **Backtracking:** If it reaches a leaf without finding the target, it needs to check the `right` children. 
3.  **The "Right-Turn" Logic:**
    * If a node has no right child (or we've already finished visiting its right child), that node is "done." It gets popped off the stack.
    * If a node *does* have a right child we haven't visited, the algorithm moves there.



### The Result Phase
* **Success:** If `root->data == target` is found, the search stops. At this exact moment, **the stack contains every node passed through to get there**. These are the ancestors. The code then loops through the stack and prints them.
* **Failure:** If the stack becomes empty and the target wasn't found, the function returns `false`.

---

## 2. Key Components
* **`struct node`**: A standard structure for a tree node containing an integer (`data`) and two pointers (`left`, `right`).
* **`newnode()`**: A helper function that allocates memory for a new node and initializes its children to `NULL`.
* **`main()`**: Sets up a specific tree structure and calls the function to find the ancestors of the value **7**.

---

## 3. Dry Run Example
Using the tree in your `main()` function:
```text
      1
     / \
    2   3
   / \
  4   5
 /
7
```
1.  **Push 1, Push 2, Push 4, Push 7.**
2.  The loop hits `root->data == target` (since root is now 7).
3.  The stack currently holds: `[1, 2, 4]` (bottom to top).
4.  The code pops and prints: **4 2 1**.

---

## 4. Complexity Analysis
* **Time Complexity:** $O(n)$, where $n$ is the number of nodes in the tree, as we may visit every node once.
* **Space Complexity:** $O(h)$, where $h$ is the height of the tree, representing the maximum size of the stack.

> [!NOTE]
> This iterative approach is generally safer than recursion for very deep trees because it avoids the risk of a **Stack Overflow** (using the heap-based `std::stack` instead of the function call stack).

Would you like me to rewrite this using a simpler **recursive** approach so you can compare the two styles?

*/

// Code 2

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to print ancestors of a given target
void printAncestors(Node* root, int target) {
    if (root == nullptr) return;

    stack<Node*> st;
    Node* lastVisited = nullptr;

    while (!st.empty() || root != nullptr) {
        // 1. Reach the leftmost node
        if (root != nullptr) {
            st.push(root);
            root = root->left;
        } 
        else {
            Node* peekNode = st.top();

            // 2. If right child exists and traversing from left child, move right
            if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                root = peekNode->right;
            } 
            else {
                // 3. Process the node (Post-order point)
                if (peekNode->data == target) {
                    st.pop(); // Remove target itself from ancestors list
                    cout << "Ancestors: ";
                    while (!st.empty()) {
                        cout << st.top()->data << " ";
                        st.pop();
                    }
                    return;
                }
                
                lastVisited = st.top();
                st.pop();
            }
        }
    }
    cout << "Target node not found in the tree.";
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->left->left = new Node(7);

    printAncestors(root, 7);

    return 0;
}

/*

This code uses a **Post-order Traversal** logic (Left-Right-Root) to find the ancestors of a node. The clever part is that in a post-order traversal, when you reach a specific node, all its ancestors are currently sitting in the stack waiting to be processed.

Here is the breakdown of how this iterative process works:

---

## 1. The Three Stages of the Loop
The `while` loop simulates the recursion stack manually. It handles three distinct scenarios:

### Stage 1: The "Dive" (Going Left)
```cpp
if (root != nullptr) {
    st.push(root);
    root = root->left;
}
```
The code keeps pushing nodes onto the stack and moving to the left child. This builds the "breadcrumb trail" from the root down to the leftmost leaf.

### Stage 2: The "Check" (Peek at Right)
When we hit a `NULL` (the end of a left branch), we look at the top of the stack (`peekNode`). 
* If that node has a **right child** that we haven't visited yet (`lastVisited != peekNode->right`), we move to that right child and start the "Dive" again.



### Stage 3: The "Process" (Post-order Point)
If there is no right child, or we just finished visiting the right child, we have officially finished exploring that subtree. 
* **The Target Check:** This is where we check `if (peekNode->data == target)`.
* If it matches, we stop everything. Because of how we traversed, **every node currently in the stack is an ancestor of the target**.

---

## 2. Key Variables
* **`st` (The Stack):** Stores the current path from the root. At any point, if the `target` is found, the stack contains exactly the ancestors.
* **`lastVisited`:** This is crucial. It keeps track of the node we just popped. It tells the code: "Hey, I just came back from the right side, don't go back down there again," preventing an infinite loop.

---

## 3. Visualizing the "Stack Trace"
Using the tree from your `main()` function, let's look for **7**:

| Step | Current Node | Stack (Bottom to Top) | lastVisited | Action |
| :--- | :--- | :--- | :--- | :--- |
| 1 | 1 | `[1]` | `null` | Push 1, move left to 2 |
| 2 | 2 | `[1, 2]` | `null` | Push 2, move left to 4 |
| 3 | 4 | `[1, 2, 4]` | `null` | Push 4, move left to 7 |
| 4 | 7 | `[1, 2, 4, 7]` | `null` | Push 7, move left to `null` |
| 5 | `null` | `[1, 2, 4, 7]` | `null` | Peek 7. No right child? Match target! |

**Once target 7 is matched:**
1. Pop 7 (the target itself).
2. The stack remains: `[1, 2, 4]`.
3. The loop prints these: **4, 2, 1**.



---

## 4. Why is this better than the first version?
Your first code snippet used a more complex set of nested `while` loops. This version is a **standard implementation of Post-order traversal**. It is:
* **Cleaner:** The logic for moving left, right, and popping is clearly separated.
* **Reliable:** It uses the `lastVisited` pattern, which is the industry-standard way to do iterative post-order traversal.

Would you like me to show you how to modify this to return a `vector<int>` of ancestors instead of just printing them?

*/

// Code 3

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm> // for reverse

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Returns a vector containing ancestors from root to target
vector<int> getAncestors(Node* root, int target) {
    vector<int> ancestors;
    if (root == nullptr) return ancestors;

    stack<Node*> st;
    Node* lastVisited = nullptr;

    while (!st.empty() || root != nullptr) {
        if (root != nullptr) {
            st.push(root);
            root = root->left;
        } 
        else {
            Node* peekNode = st.top();

            if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                root = peekNode->right;
            } 
            else {
                // If we found the target, the current stack IS the path
                if (peekNode->data == target) {
                    st.pop(); // Remove target itself
                    while (!st.empty()) {
                        ancestors.push_back(st.top()->data);
                        st.pop();
                    }
                    return ancestors;
                }
                
                lastVisited = st.top();
                st.pop();
            }
        }
    }
    return ancestors; // Returns empty vector if target not found
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->left->left = new Node(7);

    vector<int> result = getAncestors(root, 7);

    if (result.empty()) {
        cout << "No ancestors found.";
    } else {
        cout << "Ancestors: ";
        for (int val : result) cout << val << " ";
    }

    return 0;
}