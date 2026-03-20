// C++ program to check if a node exists in a binary tree
#include <iostream>
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

// Function to traverse the tree in preorder and check if the given node exists in it
bool ifNodeExists(Node* root, int key) {
    if (root == nullptr)
        return false;

    if (root->data == key)
        return true;

    // then recur on left subtree
    bool res1 = ifNodeExists(root->left, key);
    
    // node found, no need to look further
    if (res1) return true; 

    // node is not found in left, so recur on right subtree
    bool res2 = ifNodeExists(root->right, key);

    return res2;
}

int main() {
   
    // Binary tree  
    //          0
    //        /  \
    //       1    2
    //      / \   / \
    //     3   4 5   6
    //    /   / \
    //   7   8   9
    Node* root = new Node(0);
    root->left = new Node(1);
    root->left->left = new Node(3);
    root->left->left->left = new Node(7);
    root->left->right = new Node(4);
    root->left->right->left = new Node(8);
    root->left->right->right = new Node(9);
    root->right = new Node(2);
    root->right->left = new Node(5);
    root->right->right = new Node(6);

    int key = 4;

    if (ifNodeExists(root, key))
        cout << "True";
    else
        cout << "False";

    return 0;
}

// Code 2

#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to search for a value iteratively
bool search(Node* root, int target) {
    if (root == nullptr) return false;

    // Use a queue for Level-Order Traversal (BFS)
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        // Check if current node contains the target
        if (curr->data == target) {
            return true;
        }

        // Add children to the queue to explore the next level
        if (curr->left != nullptr) {
            q.push(curr->left);
        }
        if (curr->right != nullptr) {
            q.push(curr->right);
        }
    }

    // If the queue becomes empty, the target is not in the tree
    return false;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    int target = 5;
    if (search(root, target)) {
        cout << "Element " << target << " found in the tree." << endl;
    } else {
        cout << "Element " << target << " not found." << endl;
    }

    return 0;
}