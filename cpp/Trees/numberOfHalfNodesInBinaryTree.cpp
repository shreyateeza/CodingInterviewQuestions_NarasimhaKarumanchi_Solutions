// C++ program to count half nodes in a Binary Tree 
#include <bits/stdc++.h> 
using namespace std; 

// A binary tree Node has data, pointer to left 
// child and a pointer to right child 
struct Node 
{ 
	int data; 
	struct Node* left, *right; 
}; 

// Function to get the count of half Nodes in 
// a binary tree 
unsigned int gethalfCount(struct Node* node) 
{ 
	// If tree is empty 
	if (!node) 
		return 0; 

	int count = 0; // Initialize count of half nodes 

	// Do level order traversal starting from root 
	queue<Node *> q; 
	q.push(node); 
	while (!q.empty()) 
	{ 
		struct Node *temp = q.front(); 
		q.pop(); 

		if (!temp->left && temp->right || 
			temp->left && !temp->right) 
			count++; 

		if (temp->left != NULL) 
			q.push(temp->left); 
		if (temp->right != NULL) 
			q.push(temp->right); 
	} 
	return count; 
} 

/* Helper function that allocates a new 
Node with the given data and NULL left 
and right pointers. */
struct Node* newNode(int data) 
{ 
	struct Node* node = new Node; 
	node->data = data; 
	node->left = node->right = NULL; 
	return (node); 
} 

// Driver program 
int main(void) 
{ 
	/* 2 
	/ \ 
	7	 5 
	\	 \ 
	6	 9 
	/ \ / 
	1 11 4 
	Let us create Binary Tree shown in 
	above example */

	struct Node *root = newNode(2); 
	root->left	 = newNode(7); 
	root->right	 = newNode(5); 
	root->left->right = newNode(6); 
	root->left->right->left = newNode(1); 
	root->left->right->right = newNode(11); 
	root->right->right = newNode(9); 
	root->right->right->left = newNode(4); 

	cout << gethalfCount(root); 

	return 0; 
} 
