// C++ program to find the diameter
// of a binary tree.
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

// Recursive function which finds the 
// height of root and also calculates 
// the diameter of the tree.
int diameterRecur(Node* root, int &ans) {
  
    // Base case: tree is empty
    if (root == nullptr)
        return 0;
    
    // find the height of left and right subtree
    // (it will also find of diameter for left 
    // and right subtree).
    int lHeight = diameterRecur(root->left, ans);
    int rHeight = diameterRecur(root->right, ans);
    
    // Check if diameter of root is greater
    // than ans.
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