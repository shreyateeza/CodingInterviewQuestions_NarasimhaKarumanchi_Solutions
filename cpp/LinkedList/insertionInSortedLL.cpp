#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		next = nullptr;
	}
};

class LinkedList {
private:
	Node* head;

public:
	LinkedList() {
		head = nullptr;
	}

	void sortedInsert(Node* new_node) {
		if (head == nullptr) {
			head = new_node;
			return;
		}

		Node* prev = nullptr;
		Node* current = head;
		while (current && current->data < new_node->data) {
			prev = current;
			current = current->next;
		}

		if (prev == nullptr) {
			new_node->next = head;
			head = new_node;
		}
		else {
			new_node->next = current;
			prev->next = new_node;
		}
	}

	void push(int data) {
		Node* new_node = new Node(data);
		new_node->next = head;
		head = new_node;
	}

	void printList() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
};

int main() {
	LinkedList llist;
	Node* new_node = new Node(5);
	llist.sortedInsert(new_node);
	new_node = new Node(10);
	llist.sortedInsert(new_node);
	new_node = new Node(7);
	llist.sortedInsert(new_node);
	new_node = new Node(3);
	llist.sortedInsert(new_node);
	new_node = new Node(1);
	llist.sortedInsert(new_node);
	new_node = new Node(9);
	llist.sortedInsert(new_node);
	cout << "Create Linked List" << endl;
	llist.printList();
	return 0;
}
