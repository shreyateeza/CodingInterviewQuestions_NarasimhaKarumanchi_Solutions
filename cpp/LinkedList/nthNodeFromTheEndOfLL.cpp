/* This is the ListNode class definition

class ListNode {
public:
	int data;
	ListNode* next;

	ListNode(int data) {
		this->data = data;
		this->next = NULL;
	}
};
*/

ListNode* xthNodeFromEnd(ListNode* head, int x) {
	// add your logic here
	ListNode *fast = head, *slow = head;
	while(x>0){
		fast = fast->next;
		x--;
	}
	while(fast != NULL){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}