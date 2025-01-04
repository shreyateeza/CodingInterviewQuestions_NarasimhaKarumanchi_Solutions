// C++ program to find Vertical Sum in
// a given Binary Tree

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

// Traverses the tree in in-order form and
// populates a hashMap that contains the
// vertical sum
void verticalSumUtil(Node *node, int hd, unordered_map<int, int> &mp, 
                     int &mn, int &mx) {
    // Base case
    if (node == nullptr) return;

    // Recur for left subtree
    verticalSumUtil(node->left, hd-1, mp, mn, mx);

    // Add val of current node to
    // map entry of corresponding hd
    mp[hd] += node->data;
    mn = min(mn, hd);
      mx = max(mx, hd);
  
    // Recur for right subtree
    verticalSumUtil(node->right, hd+1, mp, mn, mx);
}

// Function to find vertical sum
vector<int> verticalSum(Node *root) {
  
    // a map to store sum of nodes for each 
    // horizontal distance
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