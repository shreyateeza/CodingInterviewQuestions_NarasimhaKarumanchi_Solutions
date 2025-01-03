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

int getMiddleElementOfLinkedList (ListNode* list) {
    // add your logic here
	if(!list) return -1;
	ListNode *slow = list, *fast = list;
	while(fast->next!=NULL && fast->next->next!=NULL){
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow->data;
}