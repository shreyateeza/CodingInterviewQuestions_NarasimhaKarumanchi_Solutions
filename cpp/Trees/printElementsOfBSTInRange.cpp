// C++ program to print BST
// in a given range
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node (int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// Recursive function to append nodes that lie in the given range.
void appendNodes(Node* root, int n1, int n2, vector<int> &ans) {
    if (root==nullptr) return;
    
    // If the curr node lies in the range, process left subtree, append curr node 
    // and process right subtree (to perform in-order)
    if (root->data >= n1 && root->data<= n2) {
        appendNodes(root->left, n1, n2, ans);
        ans.push_back(root->data);
        appendNodes(root->right, n1, n2, ans);
    }
    
    // If curr node is less than low, then process right subtree.
    else if(root->data < n1) {
        appendNodes(root->right, n1, n2, ans);
    }
    
    // If curr node is greater than high, then process left subtree.
    else {
        appendNodes(root->left, n1, n2, ans);
    }
}

// Main function
vector<int> printNearNodes(Node *root, int n1, int n2) {
    
    vector<int> ans;
    appendNodes(root, n1, n2, ans);
    return ans;
}

int main() {
    
    // BST
    //       22
    //      /  \
    //    12    30
    //   /  \
    //  8    20
    Node* root = new Node(22);
    root->left = new Node(12);
    root->right = new Node(30);
    root->left->left = new Node(8);
    root->left->right = new Node(20);
    int n1 = 10, n2 = 22;
    vector<int> ans = printNearNodes(root, n1, n2);
    
    for (auto num: ans) cout << num << " ";
    cout << endl;
    
    return 0;
}


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

void printRange(Node* root, int L, int R) {
    if (root == nullptr) return;

    stack<Node*> st;
    Node* curr = root;

    cout << "Elements in range [" << L << ", " << R << "]: ";

    while (!st.empty() || curr != nullptr) {
        // 1. Reach the leftmost node of the current subtree
        while (curr != nullptr) {
            st.push(curr);
            
            // Optimization: If curr->data < L, left subtree won't be in range
            if (curr->data > L)
                curr = curr->left;
            else
                curr = nullptr; // Stop going left
        }

        curr = st.top();
        st.pop();

        // 2. Check if the current node is within range
        if (curr->data >= L && curr->data <= R) {
            cout << curr->data << " ";
        }

        // 3. Move to the right child
        // Optimization: If curr->data > R, right subtree won't be in range
        if (curr->data < R)
            curr = curr->right;
        else
            curr = nullptr; // Stop going right
    }
    cout << endl;
}

int main() {
    // Constructing a sample BST
    //        20
    //       /  \
    //      8    22
    //     / \
    //    4   12
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);

    int L = 10, R = 25;
    printRange(root, L, R);

    return 0;
}