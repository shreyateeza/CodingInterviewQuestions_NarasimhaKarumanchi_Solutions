// C++ Program to convert a Binary Tree to a Circular Doubly Linked List 
#include <iostream> 
using namespace std; 

// To represents a node of a Binary Tree 
struct Node { 
	struct Node *left, *right; 
	int data; 
}; 

// A function that appends rightList at the end of leftList. 
Node* concatenate(Node* leftList, Node* rightList) 
{ 
	// If either of the list is empty then return the other list 
	if (leftList == NULL) 
		return rightList; 
	if (rightList == NULL) 
		return leftList; 

	// Store the last Node of left List 
	Node* leftLast = leftList->left; 

	// Store the last Node of right List 
	Node* rightLast = rightList->left; 

	// Connect the last node of Left List with the first Node of the right List 
	leftLast->right = rightList; 
	rightList->left = leftLast; 

	// Left of first node points to the last node in the list 
	leftList->left = rightLast; 

	// Right of last node refers to the first node of the List 
	rightLast->right = leftList; 

	return leftList; 
} 

// Function converts a tree to a circular Linked List and then returns the head of the Linked List 
Node* bTreeToCList(Node* root) 
{ 
	if (root == NULL) 
		return NULL; 

	// Recursively convert left and right subtrees 
	Node* left = bTreeToCList(root->left); 
	Node* right = bTreeToCList(root->right); 

	// Make a circular linked list of single node 
	// (or root). To do so, make the right and 
	// left pointers of this node point to itself 
	root->left = root->right = root; 

	// Step 1 (concatenate the left list with the list 
	//		 with single node, i.e., current node) 
	// Step 2 (concatenate the returned list with the 
	//		 right List) 
	return concatenate(concatenate(left, root), right); 
} 

// Display Circular Link List 
void displayCList(Node* head) 
{ 
	cout << "Circular Linked List is :\n"; 
	Node* itr = head; 
	do { 
		cout << itr->data << " "; 
		itr = itr->right; 
	} while (head != itr); 
	cout << "\n"; 
} 

// Create a new Node and return its address 
Node* newNode(int data) 
{ 
	Node* temp = new Node(); 
	temp->data = data; 
	temp->left = temp->right = NULL; 
	return temp; 
} 

// Driver Program to test above function 
int main() 
{ 
	Node* root = newNode(10); 
	root->left = newNode(12); 
	root->right = newNode(15); 
	root->left->left = newNode(25); 
	root->left->right = newNode(30); 
	root->right->left = newNode(36); 

	Node* head = bTreeToCList(root); 
	displayCList(head); 

	return 0; 
} 


/*

This C++ code uses a clever recursive approach to transform a **Binary Tree** into a **Circular Doubly Linked List (CDLL)**. The order of the nodes in the final list follows an **In-order Traversal** (Left -> Root -> Right).

---

### 1. The Core Idea: Divide and Conquer

The algorithm treats every node as a tiny, one-element circular list. It then merges these lists together.

* **Left Subtree:** Converted into a CDLL.
* **Root:** Converted into a single-node CDLL.
* **Right Subtree:** Converted into a CDLL.

The final step for every recursive call is to concatenate: `(Left CDLL) + (Root) + (Right CDLL)`.

---

### 2. Detailed Function Breakdown

#### `concatenate(leftList, rightList)`

This is the workhorse of the code. It takes two circular lists and stitches them together.

1. **Find the Ends:** Since these are circular, the "last" node of a list is always found at `List->left`.
2. **Break the Circles:** It identifies `leftLast` and `rightLast`.
3. **Bridge the Gap:** * Connects `leftLast` to `rightList` (forward link).
* Connects `rightList` to `leftLast` (backward link).


4. **Close the New Circle:** * Connects the very first node (`leftList`) back to the very last node (`rightLast`).
* Connects the very last node (`rightLast`) forward to the very first node (`leftList`).



#### `bTreeToCList(root)`

This is the recursive wrapper.

* **Base Case:** If the node is NULL, return NULL.
* **Recursive Step:** Call the function for left and right children.
* **Single Node CDLL:** It turns the current `root` into a circular list by making its `left` and `right` point to itself (`root->left = root->right = root`).
* **Merge:** It calls `concatenate` twice to join the left list with the root, and then that result with the right list.

---

### 3. Complexity Analysis

#### Time Complexity: $O(N)$

* Each node in the binary tree is visited exactly once.
* The `concatenate` function performs a constant number of pointer assignments ($O(1)$) because it directly accesses the "last" node using the `left` pointer, rather than traversing the whole list.

#### Space Complexity: $O(H)$

* $H$ is the height of the tree.
* This space is used by the **recursion stack**.
* In a balanced tree, this is $O(\log N)$. In a skewed tree (like a linked list), it is $O(N)$.

---

### 4. Why is this efficient?

Usually, to find the end of a linked list, you have to walk from the head to the tail ($O(N)$). However, because this implementation maintains the **circular** property during every step of the recursion, the `left` pointer of any "head" node always acts as a shortcut to the "tail." This keeps the merging process extremely fast.

**Would you like me to trace a small example (like a 3-node tree) step-by-step to show exactly how the pointers shift?**

*/