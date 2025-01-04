// A C++ program to find value of the
// deepest node in a given binary tree
#include <bits/stdc++.h>
using namespace std;

// A tree node with constructor
class Node
{
public:
	int data;
	Node *left, *right;
	
	// constructor 
	Node(int key)
	{
		data = key;
		left = NULL;
		right = NULL;
	}
};

// Function to return the deepest node
Node* deepestNode(Node* root)
{
	Node* tmp = NULL;
	if (root == NULL)
		return NULL;

	// Creating a Queue
	queue<Node*> q;
	q.push(root);

	// Iterates until queue become empty
	while (q.size() > 0)
	{
		tmp = q.front();
		q.pop();
		if (tmp->left != NULL)
			q.push(tmp->left);
		if (tmp->right != NULL)
			q.push(tmp->right);
	}
	return tmp;
}
	
int main()
{
	Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->right->left = new Node(5);
	root->right->right = new Node(6);
	root->right->left->right = new Node(7);
	root->right->right->right = new Node(8);
	root->right->left->right->left = new Node(9);

	Node* deepNode = deepestNode(root);
	cout << (deepNode->data);

	return 0;
}
