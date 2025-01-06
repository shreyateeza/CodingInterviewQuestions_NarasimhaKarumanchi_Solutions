// C++ program to demonstrate deletion in
// Ternary Search Tree (TST)
// For insert and other functions, refer
// https://www.geeksforgeeks.org/ternary-search-tree

#include<bits/stdc++.h>
using namespace std;

// structure of a node in TST
struct Node
{
	char key;
	int isleaf;
	struct Node *left;
	struct Node *eq;
	struct Node *right;
};

// function to create a node in TST
struct Node *createNode(char key)
{
	struct Node *temp = new Node;
	temp->key = key;
	temp->isleaf = 0;
	temp->left = NULL;
	temp->eq = NULL;
	temp->right = NULL;
	return temp;
};

// function to insert a Node in TST
void insert_node(struct Node **root, string s)
{
	if((int)s.length()==0)
		return;
	if (!(*root))
	{
		(*root) = createNode(s[0]);
		// return;
	}

	if ((s[0])<(*root)->key)
		insert_node( &(*root)->left, s);

	else if ((s[0])>(*root)->key)
		insert_node( &(*root)->right, s);

	else if ((s[0]) == (*root)->key)
	{
		if ((int)s.length() == 1)
		{
			(*root)->isleaf = 1;
			return;
		}
		insert_node( &(*root)->eq, s.substr(1));
	}
}

// function to display the TST
void display(struct Node *root, char str[], int level)
{
	if (!root)
		return;

	display(root->left, str, level);
	str[level] = root->key;

	if (root->isleaf == 1)
	{
		str[level+1] = '\0';
		cout<< str <<endl;
	}

	display(root->eq, str, level+1);
	display(root->right, str, level);
}

//to check if current node is leaf node or not
int isLeaf(struct Node *root)
{
	return root->isleaf == 1;
}

// to check if current node has any child
// node or not
int isFreeNode(struct Node *root)
{
	if (root->left ||root->eq ||root->right)
		return 0;
	return 1;
}

// function to delete a string in TST
int delete_node(struct Node *root, string str,
				int level, int n)
{
	if (root == NULL)
		return 0;


	// CASE 4 Key present in TST, having atleast
	// one other key as prefix key.
	if (str[level+1] == '\0')
	{
		// Unmark leaf node if present
		if (isLeaf(root))
		{
			root->isleaf = 0;
			return isFreeNode(root);
		}

		// else string is not present in TST and
		// return 0
		else
			return 0;
	}

	// CASE 3 Key is prefix key of another long
	// key in TST.
	if (str[level] < root->key)
		return delete_node(root->left, str, level, n);
	if (str[level] > root->key)
		return delete_node(root->right, str, level, n);

	// CASE 1 Key may not be there in TST.
	if (str[level] == root->key)
	{
		// CASE 2 Key present as unique key
		if (delete_node(root->eq, str, level+1, n))
		{
			// delete the last node, neither it has
			// any child nor it is part of any other
			// string
			delete(root->eq);
			return !isLeaf(root) && isFreeNode(root);
		}
	}

	return 0;
}

// Driver function
int main()
{
	struct Node *temp = NULL;

	insert_node(&temp, "CAT");
	insert_node(&temp, "BUGS");
	insert_node(&temp, "CATS");
	insert_node(&temp, "UP");

	int level = 0;
	char str[20];
	int p = 0;

	cout << "1.Content of the TST before deletion:\n";
	display(temp, str, 0);

	level = 0;
	delete_node(temp,"CAT", level, 5);

	level = 0;
	cout << "\n2.Content of the TST after deletion:\n";
	display(temp, str, level);
	return 0;
}
