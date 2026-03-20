#include <bits/stdc++.h>
using namespace std;

/* A Doubly Linked List node that
will also be used as a tree node */
class Node 
{ 
	public:
	int data; 

	// For tree, next pointer can be
	// used as right subtree pointer 
	Node* next; 

	// For tree, prev pointer can be
	// used as left subtree pointer 
	Node* prev; 
}; 

// A utility function to count nodes in a Linked List 
int countNodes(Node *head); 

Node* sortedListToBSTRecur(Node **head_ref, int n); 

/* This function counts the number of 
nodes in Linked List and then calls 
sortedListToBSTRecur() to construct BST */
Node* sortedListToBST(Node *head) 
{ 
	/*Count the number of nodes in Linked List */
	int n = countNodes(head); 

	/* Construct BST */
	return sortedListToBSTRecur(&head, n); 
} 

/* The main function that constructs 
balanced BST and returns root of it. 
head_ref --> Pointer to pointer to
head node of Doubly linked list 
n --> No. of nodes in the Doubly Linked List */
Node* sortedListToBSTRecur(Node **head_ref, int n) 
{ 
	/* Base Case */
	if (n <= 0) 
		return NULL; 

	/* Recursively construct the left subtree */
	Node *left = sortedListToBSTRecur(head_ref, n/2); 

	/* head_ref now refers to middle node,
	make middle node as root of BST*/
	Node *root = *head_ref; 

	// Set pointer to left subtree 
	root->prev = left; 

	/* Change head pointer of Linked List
	for parent recursive calls */
	*head_ref = (*head_ref)->next; 

	/* Recursively construct the right 
	subtree and link it with root 
	The number of nodes in right subtree
	is total nodes - nodes in 
	left subtree - 1 (for root) */
	root->next = sortedListToBSTRecur(head_ref, n-n/2-1); 

	return root; 
} 

/* UTILITY FUNCTIONS */
/* A utility function that returns 
count of nodes in a given Linked List */
int countNodes(Node *head) 
{ 
	int count = 0; 
	Node *temp = head; 
	while(temp) 
	{ 
		temp = temp->next; 
		count++; 
	} 
	return count; 
} 

/* Function to insert a node at 
the beginning of the Doubly Linked List */
void push(Node** head_ref, int new_data) 
{ 
	/* allocate node */
	Node* new_node = new Node();

	/* put in the data */
	new_node->data = new_data; 

	/* since we are adding at the beginning, 
	prev is always NULL */
	new_node->prev = NULL; 

	/* link the old list of the new node */
	new_node->next = (*head_ref); 

	/* change prev of head node to new node */
	if((*head_ref) != NULL) 
	(*head_ref)->prev = new_node ; 

	/* move the head to point to the new node */
	(*head_ref) = new_node; 
} 

/* Function to print nodes in a given linked list */
void printList(Node *node) 
{ 
	while (node!=NULL) 
	{ 
		cout<<node->data<<" "; 
		node = node->next; 
	} 
} 

/* A utility function to print
preorder traversal of BST */
void preOrder(Node* node) 
{ 
	if (node == NULL) 
		return; 
	cout<<node->data<<" "; 
	preOrder(node->prev); 
	preOrder(node->next); 
} 

/* Driver code*/
int main() 
{ 
	/* Start with the empty list */
	Node* head = NULL; 

	/* Let us create a sorted linked list to test the functions 
	Created linked list will be 7->6->5->4->3->2->1 */
	push(&head, 7); 
	push(&head, 6); 
	push(&head, 5); 
	push(&head, 4); 
	push(&head, 3); 
	push(&head, 2); 
	push(&head, 1); 

	cout<<"Given Linked List\n"; 
	printList(head); 

	/* Convert List to BST */
	Node *root = sortedListToBST(head); 
	cout<<"\nPreOrder Traversal of constructed BST \n "; 
	preOrder(root); 

	return 0; 
} 


/*

This code implements an efficient, **bottom-up recursion** to convert a **Sorted Doubly Linked List (DLL)** into a **Balanced Binary Search Tree (BST)**.

The genius of this specific implementation is its **$O(n)$ time complexity**. Most naive solutions find the middle element repeatedly, which takes $O(n \log n)$. This version "consumes" the list nodes in order as it builds the tree from the leaves up to the root.

---

## 1. How the Logic Works

### The Dual-Purpose Node
The `Node` class is used for both the list and the tree:
* **In DLL:** `prev` is the previous node, `next` is the next node.
* **In BST:** `prev` becomes the **left child**, `next` becomes the **right child**.

### The Bottom-Up Strategy
Instead of finding the middle of the list first, the function `sortedListToBSTRecur` follows these steps:
1.  **Build Left:** Recursively build the left subtree using the first $n/2$ nodes.
2.  **Build Root:** The `head_ref` will now be pointing at the exactly correct "middle" node for the current subtree. We pick this as our `root`.
3.  **Link Left:** Connect the `left` subtree built in step 1 to `root->prev`.
4.  **Move Forward:** Increment the `head_ref` to the next node in the list.
5.  **Build Right:** Recursively build the right subtree using the remaining nodes.



---

## 2. Key Code Sections Explained

### The `head_ref` Pointer (`Node**`)
Notice that the function takes a **pointer to a pointer**. This is crucial. It allows the recursive calls to actually move the "head" of the list forward. When the left subtree finishes building, the original `head` pointer has moved several steps forward, landing perfectly on the node that should be the parent.

### The Shift Calculation
```cpp
Node *left = sortedListToBSTRecur(head_ref, n/2);
...
root->next = sortedListToBSTRecur(head_ref, n - n/2 - 1);
```
This ensures the tree remains **balanced**. If $n=7$, it builds 3 nodes on the left, 1 for the root, and 3 nodes on the right.

---

## 3. Complexity Analysis

### Time Complexity: $O(n)$
* The function visits each node in the linked list exactly once. 
* Unlike the top-down approach (which calls `countNodes` or searches for the middle at every level), this only counts the nodes **once** at the beginning.

### Space Complexity: $O(\log n)$
* This is the space used by the recursion stack. Since we are building a balanced tree, the maximum depth of the stack is the height of the tree, which is $\log n$.

---

## 4. Visual Execution (Example: 1-2-3-4-5-6-7)

1.  We want to build a tree of 7 nodes.
2.  Recursion goes left for 3 nodes (1, 2, 3).
3.  Inside that, it goes left for 1 node (Node 1).
4.  **Node 1** becomes a leaf. `head_ref` moves to **Node 2**.
5.  **Node 2** becomes the root for the left side. `head_ref` moves to **Node 3**.
6.  **Node 3** becomes the right child of Node 2.
7.  Now the left side is done. The main root picks **Node 4** (the current `head_ref`).



Would you like me to show you how to add a `deleteList` function to this code to prevent memory leaks after the BST is destroyed?

*/


#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// --- CORE RECURSIVE LOGIC ---
// Using a reference to a pointer (Node* &head_ref)
Node* sortedListToBSTRecur(Node* &head_ref, int n) {
    if (n <= 0) return NULL;

    // Recursively construct the left subtree
    Node* left = sortedListToBSTRecur(head_ref, n / 2);

    // head_ref now refers to middle node, make it the root
    Node* root = head_ref;
    root->prev = left;

    // Move head pointer forward for parent recursive calls
    // This updates the pointer in the parent scope directly
    head_ref = head_ref->next;

    // Construct the right subtree
    root->next = sortedListToBSTRecur(head_ref, n - n / 2 - 1);

    return root;
}

int countNodes(Node* head) {
    int count = 0;
    while (head) {
        head = head->next;
        count++;
    }
    return count;
}

Node* sortedListToBST(Node* head) {
    int n = countNodes(head);
    // Passing the head pointer by reference
    return sortedListToBSTRecur(head, n);
}

// --- UTILITY FUNCTIONS ---

// Modified to use reference to pointer
void push(Node* &head_ref, int new_data) {
    Node* new_node = new Node(new_data);
    new_node->next = head_ref;

    if (head_ref != NULL)
        head_ref->prev = new_node;

    head_ref = new_node;
}

void printList(Node* node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

void preOrder(Node* node) {
    if (node == NULL) return;
    cout << node->data << " ";
    preOrder(node->prev);
    preOrder(node->next);
}

int main() {
    Node* head = NULL;

    // List: 1 2 3 4 5 6 7
    push(head, 7);
    push(head, 6);
    push(head, 5);
    push(head, 4);
    push(head, 3);
    push(head, 2);
    push(head, 1);

    cout << "Given Linked List:\n";
    printList(head);

    Node* root = sortedListToBST(head);

    cout << "\nPreOrder Traversal of constructed BST:\n";
    preOrder(root);
    cout << endl;

    return 0;
}


/*

To visualize this function, you have to stop thinking of it as "finding the middle" and start thinking of it as **"assembling a puzzle from left to right."**

Because we are using `Node* &head_ref` (a reference), there is only **one** pointer moving through the list across all recursive calls. It moves like a typewriter, processing one node at a time.

---

### 1. The "Typewriter" Visualization
Imagine your sorted Doubly Linked List is a row of tiles: `[1] - [2] - [3] - [4] - [5] - [6] - [7]`.

* **The Left Subtree:** The function first dives deep into the left side. It doesn't pick a root yet; it just keeps going left until it hits the base case (`n=0`).
* **The First Node:** The first time the code actually executes `root = head_ref`, it is at the very first node `[1]`. It turns `[1]` into a leaf.
* **The Move:** `head_ref = head_ref->next` moves the "typewriter" to `[2]`.
* **The Root:** Now that the left side of `[2]` is done, `[2]` becomes a parent.
* **The Right:** Then it moves to the right to handle `[3]`.



---

### 2. Step-by-Step Execution (For $n=3$)
Let's trace a list with nodes `1, 2, 3`.

**Step 1: Go Left**
* Call `sortedListToBSTRecur(head, 3)`.
* It calculates `n/2 = 1`. It calls itself: `Recur(head, 1)`.
* Inside that, it calls `Recur(head, 0)`, which returns `NULL`.

**Step 2: Capture Node 1**
* Now back in `Recur(head, 1)`:
    * `left` = `NULL`.
    * `root` = `head_ref` (which is **Node 1**).
    * `head_ref` moves to **Node 2**.
    * `right` call for 0 nodes returns `NULL`.
* **Result:** Node 1 is a complete mini-tree.

**Step 3: Capture Node 2 (The Parent)**
* Back in the original `Recur(head, 3)`:
    * `left` now points to **Node 1**.
    * `root` = `head_ref` (which is now **Node 2**).
    * `root->prev = left` (Node 2's left child is now Node 1).
    * `head_ref` moves to **Node 3**.

**Step 4: Go Right**
* Call `Recur(head, 1)` for the right side (where `head_ref` is **Node 3**).
* This creates a leaf for **Node 3**.
* `root->next = Node 3`.



---

### 3. Why this is $O(n)$
If you used the "Top-Down" method (find middle, then split), you would visit nodes multiple times to find the center of every sub-segment.

In **this** function:
1.  The recursion depth is $\log n$.
2.  Each node in the list is assigned as a `root` exactly **once**.
3.  The `head_ref` pointer only ever moves **forward**.

| Step | Action | Pointer Position |
| :--- | :--- | :--- |
| **Start** | Call with $n=7$ | At Node 1 |
| **Left Finish** | Nodes 1, 2, 3 processed | At Node 4 |
| **Root Finish** | Node 4 assigned as Root | At Node 5 |
| **Right Finish** | Nodes 5, 6, 7 processed | At NULL |

---

### Summary of the "Magic"
The reference `&head_ref` is the key. Without it, the "right" subtree wouldn't know that the "left" subtree and "root" had already used up the first few nodes of the list. The reference ensures the pointer always points to the **next available tile** in the list.

Would you like me to create a small table showing exactly how `n`, `n/2`, and `n - n/2 - 1` split for a larger number like $n=10$?

*/