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

ListNode* reverseLinkedList (ListNode* head) {
    // add your logic here
	if(!head) return NULL;
	ListNode *current = head, *_next = NULL, *previous = NULL;
	while(current != NULL){
		_next = current->next;
		current->next = previous;
		previous = current;
		current = _next;
	}
	return previous;
}