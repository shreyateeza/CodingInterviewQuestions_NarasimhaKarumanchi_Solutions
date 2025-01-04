// C++ Program to Implement Double Ended Queue
#include <iostream>
#include <stdexcept>
using namespace std;
// Template class for a doubly linked list based Deque
template <typename T> class Deque {
private:
    // Node structure representing each element in the Deque
    struct Node {
        // Data held by the node
        T data;
        // Pointer to the previous node
        Node* prev;
        // Pointer to the next node
        Node* next;

        // Constructor to initialize a Node with a given
        // value
        Node(T value)
            : data(value)
            , prev(nullptr)
            , next(nullptr)
        {
        }
    };
    // Pointer to the front of the Deque
    Node* front;
    // Pointer to the rear of the Deque
    Node* rear;
    // Number of elements in the Deque
    int size;

public:
    // Constructor to initialize an empty Deque
    Deque()
        : front(nullptr)
        , rear(nullptr)
        , size(0)
    {
    }

    // Destructor to clean up memory by removing all
    // elements
    ~Deque()
    {
        while (!is_empty()) {
            pop_front();
        }
    }

    // Function to add an element to the front of the Deque
    void push_front(T value)
    {
        // Create a new node
        Node* new_node = new Node(value);
        // If Deque is empty, both front and rear point to
        // the new node
        if (is_empty()) {
            front = rear = new_node;
        }
        else {
            // Link the new node to the current front
            new_node->next = front;
            // Link the current front to the new node
            front->prev = new_node;
            // Update front to the new node
            front = new_node;
        }
        // Increment the size of the Deque
        size++;
    }

    // Function to add an element to the back of the Deque
    void push_back(T value)
    {
        Node* new_node
            = new Node(value); // Create a new node
        if (is_empty()) {
            // If Deque is empty, both front  and rear point
            // to the new node
            front = rear = new_node;
        }
        else {
            // Link the new node to the current rear
            new_node->prev = rear;
            // Link the current rear to the new node
            rear->next = new_node;
            // Update rear to the new node
            rear = new_node;
        }
        // Increment the size of the Deque
        size++;
    }

    // Function to remove an element from the front of the
    // Deque
    void pop_front()
    {
        if (is_empty()) {
            // Throw an error if Deque is empty
            throw runtime_error("Deque is empty");
        }
        // Temporarily hold the front node
        Node* temp = front;
        // Move front to the next node
        front = front->next;
        if (front == nullptr) {
            // If Deque is now empty, set rear to null
            rear = nullptr;
        }
        else {
            // Otherwise, unlink the old front node
            front->prev = nullptr;
        }
        // Free the memory of the old front node
        delete temp;
        // Decrement the size of the Deque
        size--;
    }

    // Function to remove an element from the back of the
    // Deque
    void pop_back()
    {
        if (is_empty()) {
            // Throw an error if Deque is empty
            throw runtime_error("Deque is empty");
        }
        // Temporarily hold the rear node
        Node* temp = rear;
        // Move rear to the previous node
        rear = rear->prev;
        if (rear == nullptr) {
            // If Deque is now empty, set front to null
            front = nullptr;
        }
        else {
            // Otherwise, unlink the old rear node
            rear->next = nullptr;
        }
        // Free the memory of the old rear node
        delete temp;
        // Decrement the size of the Deque
        size--;
    }

    // Function to get the element at the front of the Deque
    T get_front()
    {
        if (is_empty()) {
            // Throw an error if Deque is empty
            throw runtime_error("Deque is empty");
        }
        // Return the data of the front node
        return front->data;
    }

    // Function to get the element at the rear of the Deque
    T get_rear()
    {
        if (is_empty()) {
            // Throw an error if Deque is empty
            throw runtime_error("Deque is empty");
        }
        // Return the data of the rear node
        return rear->data;
    }

    // Function to check if the Deque is empty
    bool is_empty()
    {
        // Deque is empty if size is 0
        return size == 0;
    }

    // Function to get the number of elements in the Deque
    int get_size()
    {
        // Return the current size of the Deque
        return size;
    }

    // Function to display the elements of the Deque
    void display()
    {
        // Start from the front node
        Node* current = front;
        while (current != nullptr) {
            // Print the data of the current node
            cout << current->data << " ";
            // Move to the next node
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    // Create a Deque of integers
    Deque<int> deque;

    // Push elements to the front and back
    deque.push_front(10);
    deque.push_back(20);
    deque.push_front(5);
    deque.push_back(30);

    // Display the Deque after pushes
    cout << "Deque after pushes: ";
    deque.display();

    // Get and display the front and rear elements
    cout << "Front element: " << deque.get_front() << endl;
    cout << "Rear element: " << deque.get_rear() << endl;

    // Pop elements from the front and back
    deque.pop_front();
    deque.pop_back();

    // Display the Deque after pops
    cout << "Deque after pops: ";
    deque.display();

    // Display the size of the Deque
    cout << "Size of deque: " << deque.get_size() << endl;

    return 0;
}