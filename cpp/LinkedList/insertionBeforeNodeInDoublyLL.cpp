// C++ Program to insert a node before a given node of doubly linked list

#include <iostream> 
using namespace std;

struct Node {
    int data;
    Node *next, *prev;

    Node(int new_data) {
        data = new_data;
        next = prev = NULL;
    }
};

// Function to insert a new node before a given node
// in doubly linked list
Node *insertBefore(Node *head, int key, int new_data) {

    Node *curr = head;

    // Iterate over Linked List to find the key
    while (curr != NULL) {
        if (curr->data == key)
            break;
        curr = curr->next;
    }

    // if curr becomes null means, given key is not
    // found in linked list
    if (curr == NULL)
        return head;

    // Create a new node
    Node *new_node = new Node(new_data);

    // Set prev of new node to prev of given node
    new_node->prev = curr->prev;

    // Set next of new node to given node
    new_node->next = curr;

    // Update next of given node's prev to new node
    if (curr->prev != NULL) {
        new_node->prev->next = new_node;
    }
    else {
      
        // If the current node is the head, update the head
        head = new_node;
    }

    // Update prev of given node to new node
    curr->prev = new_node;

    // Return the head of the doubly linked list
    return head;
}

void printList(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        cout << " " << curr->data;
        curr = curr->next;
    }
    cout << endl;
}

int main() {

    // Create a harcoded doubly linked list:
    // 1 <-> 3 <-> 4
    Node *head = new Node(1);
    head->next = new Node(3);
    head->next->prev = head;
    head->next->next = new Node(4);
    head->next->next->prev = head->next;

    // Print the original list
    cout << "Original Linked List:";
    printList(head);

    // Insert a new node before node with data 3
    cout << "Inserting Node with data 2 before node 3:";
    int data = 2;
    int key = 3;
    head = insertBefore(head, key, data);

    // Print the updated list
    printList(head);

    return 0;
}