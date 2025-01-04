// C++ program to insert element (in level order)
// in Binary Tree
#include <iostream>
#include <queue>
using namespace std;

class Node {
public: 
      int data;
    Node* left;
    Node* right;
    Node(int x) {
        data = x;
          left = right = nullptr;
    }
};

// Function to insert element in binary tree
Node* InsertNode(Node* root, int data) {
  
    // If the tree is empty, assign new
      // node address to root
    if (root == nullptr) {
        root = new Node(data);
        return root;
    }

    // Else, do level order traversal until we find an empty
    // place, i.e. either left child or right child of some
    // node is pointing to NULL.
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
      
          // Fron a front element in queue
        Node* curr = q.front();
        q.pop();
        
          // First check left if left is null 
          // insert node in left otherwise chaeck for right
        if (curr->left != nullptr)
            q.push(curr->left);
        else {
            curr->left = new Node(data);
            return root;
        }
    
        if (curr->right != nullptr)
            q.push(curr->right);
        else {
            curr->right = new Node(data);
            return root;
        }
    }
}

// Inorder traversal of a binary tree 
void inorder(Node* curr) {
    if (curr == nullptr)
        return;
    inorder(curr->left);
    cout << curr->data << ' ';
    inorder(curr->right);
}

int main() {
  
      // Constructing the binary tree
      //          10
    //        /    \ 
    //       11     9
    //      /      / \
    //     7      15   8
  
    Node* root = new Node(10);
    root->left = new Node(11);
      root->right = new Node(9);
    root->left->left = new Node(7);
    root->right->left = new Node(15);
    root->right->right = new Node(8);
  
    int key = 12;
    root = InsertNode(root, key);
  
      // After insertion 12 in binary tree
      //          10
    //        /    \ 
    //       11     9
    //      /  \   / \
    //     7   12 15  8

    inorder(root);

    return 0;
}