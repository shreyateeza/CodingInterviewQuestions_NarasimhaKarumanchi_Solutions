// C++ Program to split a circular linked list
// into two halves 
#include <bits/stdc++.h>
using namespace std;

class Node { 
    public:
    int data; 
    Node *next; 
    Node (int new_value){
        data = new_value;
        next = nullptr;
    }
}; 

// Function to split a list (starting with head) 
// into two lists.
pair<Node*, Node*> splitList(Node *head) { 
    Node *slow = head; 
    Node *fast = head; 
    
    if(head == nullptr) 
        return {nullptr, nullptr}; 
        
    // For odd nodes, fast->next is head and 
    // for even nodes, fast->next->next is head
    while(fast->next != head && 
          fast->next->next != head) { 
        fast = fast->next->next; 
        slow = slow->next; 
    } 
    
    // If there are even elements in list
    // then move fast
    if(fast->next->next == head) 
        fast = fast->next; 
        
    // Set the head pointer of first half
    Node* head1 = head; 
        
    // Set the head pointer of second half
    Node* head2 = slow->next; 
        
    // Make second half circular
    fast->next = slow->next; 
        
    // Make first half circular
    slow->next = head; 
    
    return {head1, head2};
} 

void printList(Node *head) { 
    Node *curr = head; 
    if(head != nullptr) { 
        do { 
        cout << curr->data << " "; 
        curr = curr->next; 
        } while(curr != head); 
          cout << endl; 
    } 
} 

int main() { 
    
    Node *head = new Node(1); 
    Node *head1 = nullptr; 
    Node *head2 = nullptr; 

    // Created linked list will be 1->2->3->4
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = head;
    
    pair<Node*, Node*> result = splitList(head); 
    head1 = result.first;
    head2 = result.second;
    
    printList(head1); 
    printList(head2);
    
    return 0; 
}