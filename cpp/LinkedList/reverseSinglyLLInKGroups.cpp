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
ListNode* reverseLinkedListKGroup(ListNode* head, int k) {
	// add your logic here
	ListNode *temp = head;
	int total = 0;
	while(temp!=NULL){
		total++;
		temp = temp->next;
	}
	if(total<k) return head;
	
	int count=0;
	ListNode *curr = head, *prev = NULL, *_next = NULL;
	while(curr != NULL && count<k){
		_next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = _next;
		count++;
	}
	if(_next != NULL){
		head->next = reverseLinkedListKGroup(_next, k);
	}
	return prev;
}