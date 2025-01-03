// C++ Program to insert a node after a given node of doubly linked list

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next, *prev;

    Node(int new_data) {
        data = new_data;
        next = prev = nullptr;
    }
};

// Function to insert a new node after a given node
// in doubly linked list
Node *insertAfter(Node *head, int key, int new_data) {

    Node *curr = head;

    // Iterate over Linked List to find the key
    while (curr != nullptr) {
        if (curr->data == key)
            break;
        curr = curr->next;
    }

    // if curr becomes null means, given key is not
    // found in linked list
    if (curr == nullptr)
        return head;

    // Create a new node
    Node *new_node = new Node(new_data);

    // Set prev of new node to given node
    new_node->prev = curr;

    // Set next of new node to next of given node
    new_node->next = curr->next;

    // Update next of given node to new node
    curr->next = new_node;

    // If the given node is not the last node of the linked list, 
      // update the prev of new node's next with new node
      if(new_node->next != nullptr) {
        new_node->next->prev = new_node;
    }

    // Return the head of the doubly linked list
    return head;
}

void printList(Node *head) {

    Node *curr = head;
    while (curr != nullptr) {
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

    // Insert a new node after node 1
    cout << "Inserting Node with data 2 after node 1 :";
    int data = 2;
    int key = 1;
    head = insertAfter(head, key, data);

    // Print the updated list
    printList(head);

    return 0;
}