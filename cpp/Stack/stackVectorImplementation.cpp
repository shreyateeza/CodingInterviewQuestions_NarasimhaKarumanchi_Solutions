// C++ program to implement stack using vector
#include <iostream>
#include <vector>

using namespace std;

class Stack {

private:
    // The vector to store stack elements
    vector<int> v;

public:
    // Function to push an element onto the stack
    void push(int data)
    {
        v.push_back(data);
        cout << "Pushed: " << data << endl;
    }

    // Function to pop an element from the stack
    int pop()
    {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop.\n";
            return -1;
        }
        int top = v.back();
        v.pop_back();
        cout << "\nPopped: " << top << endl;
        return top;
    }

    // Function to get the top element of the stack without
    // removing it
    int top()
    {
        if (isEmpty()) {
            cout << "Stack is empty. No top element.\n";
            return -1;
        }
        return v.back();
    }

    // Function to check if the stack is empty
    bool isEmpty() { return v.empty(); }
};

int main()
{
    Stack myStack;

    // Push elements onto the stack
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    myStack.push(40);

    // Pop an element from the stack and print it
    myStack.pop();

    // Get the top element of the stack and print it
    int topElement = myStack.top();
    if (topElement != -1) {
        cout << "\nTop element: " << topElement << endl;
    }

    return 0;
}