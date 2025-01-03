// C++ Program to Insert a Node At a Specific Position in
// Linked List
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

// Function to insert a node at a specific position in the
// linked list.
Node* insertAtPosition(Node* head, int position, int data)
{
    Node* newNode = new Node(data);

    // If inserting at the beginning
    if (position == 1) {
        newNode->next = head;
        head = newNode;
        return head;
    }

    Node* current = head;
    // Traverse the list to find the node before the
    // insertion point
    for (int i = 1; i < position - 1 && current != nullptr;
         ++i) {
        current = current->next;
    }

    // If the position is out of bounds
    if (current == nullptr) {
        cout << "Position is out of bounds." << endl;
        delete newNode; // Deallocate memory to prevent
                        // memory leak
        return head;
    }

    // Insert the new node at the specified position
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

void printList(Node* head)
{
    while (head != nullptr) {
        cout << " " << head->data;
        head = head->next;
    }
    cout << endl;
}

int main()
{
    // Creating the list 3->5->8->10
    Node* head = new Node(3);
    head->next = new Node(5);
    head->next->next = new Node(8);
    head->next->next->next = new Node(10);

    cout << "Linked list before insertion:";
    printList(head);

    // Insert a new node with data 12 at position 3
    int data = 12, pos = 2;
    head = insertAtPosition(head, pos, data);
    cout << "Linked list after insertion of 12 at position "
            "3:";
    printList(head);

    return 0;
}